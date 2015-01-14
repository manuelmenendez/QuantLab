#include <cmath>
#include <limits>
#include <memory>

#include <boost/math/distributions/normal.hpp>

#include "DynamicAssert.h"
#include "StandardBlackScholes.h"
#include "BasicOption.h"
#include "Result.h"

extern "C"
double IStandardBlackScholes(
	double spot,
	double strike,
	double interestRate,
	double valueDate,
	double expiry,
	double volatility,
	double dividends,
	bool isCall)
{
	ql::BasicOption<> myOption;

	myOption.Spot(spot);
	myOption.Strike(strike);
	myOption.InterestRate(interestRate);
	myOption.ValueDate(valueDate);
	myOption.Expiry(expiry);
	myOption.Volatility(volatility);
	myOption.Dividends(dividends);
	myOption.PutCall(isCall ? ql::PutCallT::Call : ql::PutCallT::Put);

	if (myOption.PutCall() == ql::PutCallT::Call)
	{
		ql::StandardBlackScholes< ql::PutCallT::Call > myBlackScholes(myOption);
		return myBlackScholes.premium();
	}

	if (myOption.PutCall() == ql::PutCallT::Put)
	{
		ql::StandardBlackScholes< ql::PutCallT::Put > myBlackScholes(myOption);
		return myBlackScholes.premium();
	}

	return 0.0;
}

namespace ql
{
	template StandardBlackScholes_BASE <ql::PutCallT::Put, ql::BasicOption <>, Result<>>;
	template StandardBlackScholes_BASE <ql::PutCallT::Call, ql::BasicOption <>, Result<>>;
	template StandardBlackScholes_BASE <ql::PutCallT::Unassigned, ql::BasicOption <>, Result<>>;

	template StandardBlackScholes <ql::PutCallT::Call, ql::BasicOption <>, Result<>>;
	template StandardBlackScholes <ql::PutCallT::Put,  ql::BasicOption <>, Result<>>;
	template StandardBlackScholes <ql::PutCallT::Unassigned, ql::BasicOption <>, Result<>>;

	template < const ql::PutCallT T, class O, class R>
	double StandardBlackScholes_BASE< T, O, R >::eps()
	{
		return  10e-12;
	}

	template < const ql::PutCallT T, class O, class R>
	double StandardBlackScholes_BASE< T, O, R >::d1()
	{
		using namespace Assert;

		const  O::PriceT & S = theOption_.Spot();
		const  O::PriceT & K = theOption_.Strike();
		const  O::InterestT & r = theOption_.InterestRate();
		const  O::DividendT & q = theOption_.Dividends();
		const  O::VolatillityT & SIG = theOption_.Volatility();
		const double T = theOption_.YearFractionToExpiry();

		dynamic_release( ( std::abs(K) > StandardBlackScholes<>::eps() ), compose(__FILE__, __LINE__, "K is zero"));
		dynamic_release( ( S / K > StandardBlackScholes<>::eps() ), compose(__FILE__, __LINE__, "S/K is negative"));
		dynamic_release( ( T > StandardBlackScholes<>::eps() ), compose(__FILE__, __LINE__, "T is negative"));

		double d1 = (std::log(S / K) + (r - q + 0.5 * SIG * SIG)* T) / (SIG * std::sqrt(T));
		return  d1;
	}

	template < const ql::PutCallT T, class O, class R>
	double StandardBlackScholes_BASE< T, O, R>::d2()
	{
		using namespace Assert;
		const O::VolatillityT & SIG = theOption_.Volatility();
		const double & T = theOption_.YearFractionToExpiry();

		dynamic_release( (T > StandardBlackScholes<>::eps()), compose(__FILE__, __LINE__, "T is negative"));
		
		const double d2 = (d1() - SIG * std::sqrt(T));
		return d2;
	}

	template < const ql::PutCallT T, class O, class R >
	double StandardBlackScholes_BASE< T, O, R >::nd1()
	{
		const boost::math::normal_distribution<> nd1(0.0, 1.0);
		const double cdf = boost::math::cdf<>(nd1, d1());
		return cdf;
	}

	template < const ql::PutCallT T, class O, class R >
	double StandardBlackScholes_BASE< T, O, R >::ndd1()
	{
		const boost::math::normal_distribution<> nd1(0.0, 1.0);
		double pdf = boost::math::pdf<>(nd1, d1());
		return pdf;
	}

	template < const ql::PutCallT T, class O, class R >
	double StandardBlackScholes_BASE< T, O, R  >::nd2()
	{
		boost::math::normal_distribution<> nd1(0.0, 1.0);
		double cdf = boost::math::cdf<>(nd1, d2());
		return cdf;
	}

	template < const ql::PutCallT T, class O, class R >
	double StandardBlackScholes_BASE< T, O, R  >::vega()
	{
		const  O::DividendT & q = theOption_.Dividends();
		const double  T = theOption_.YearFractionToExpiry();
		const  O::PriceT S = theOption_.Spot();
		double vega = ndd1() * std::exp(-q * T)  * S * std::sqrt(T);
		return vega;
	}

	template <const ql::PutCallT T, class O, class R >
	double StandardBlackScholes_BASE< T, O, R  >::gamma()
	{
		const  O::DividendT & q = theOption_.Dividends();
		const double T = theOption_.YearFractionToExpiry();
		const  O::PriceT & S = theOption_.Spot();
		const  O::VolatillityT & SIG = theOption_.Volatility();
		double gamma = ndd1() * std::exp(-q * T) / (S * SIG * std::sqrt(T));
		return gamma;
	}


	// Call
	template < class O, class R>
	double StandardBlackScholes< ql::PutCallT::Call, O, R >::premium()
	{
		const  O::PriceT & S = theOption_.Spot();
		const  O::PriceT & K = theOption_.Strike();
		const  O::InterestT & r = theOption_.InterestRate();
		const  O::DividendT & q = theOption_.Dividends();
		const  O::VolatillityT & SIG = theOption_.Volatility();

		const double T = theOption_.YearFractionToExpiry();

		Assert::dynamic((-r * T < StandardBlackScholes::eps()), Assert::compose(__FILE__, __LINE__, "-r * T is below zero"));

		const double factor = exp(-r * T);
		double premium = (std::exp(-q*T) * S * nd1() - K * factor * nd2());
		return  premium;
	}

	template <class O, class R >
	double StandardBlackScholes< ql::PutCallT::Call, O, R  >::delta()
	{
		const  O::DividendT & q = theOption_.Dividends();
		const double T = theOption_.YearFractionToExpiry();
		double delta = nd1() * std::exp(-q * T);
		return delta;
	}


	// Put
	template < class O, class R>
	double StandardBlackScholes< ql::PutCallT::Put, O, R >::premium()
	{
		const  O::PriceT & S = theOption_.Spot();
		const  O::PriceT & K = theOption_.Strike();
		const  O::InterestT & r = theOption_.InterestRate();
		const  O::DividendT & q = theOption_.Dividends();
		const  O::VolatillityT & SIG = theOption_.Volatility();

		const double T = theOption_.YearFractionToExpiry();

		Assert::dynamic((-r * T < StandardBlackScholes::eps()), Assert::compose(__FILE__, __LINE__, "-r * T is below zero"));

		const double factor = exp(-r * T);

		
		ql::StandardBlackScholes<ql::PutCallT::Call > myB(this->theOption_);
		double premiumCall = myB.premium();

		double premium = premiumCall  - S * std::exp(-q * T) + K * factor;
		return premium;
	}

	template <class O, class R >
	double StandardBlackScholes< ql::PutCallT::Put, O, R  >::delta()
	{
		const  O::DividendT & q = theOption_.Dividends();
		const double T = theOption_.YearFractionToExpiry();

		ql::StandardBlackScholes<ql::PutCallT::Call > myB(this->theOption_);
		double deltaCall = myB.delta();

		double delta = deltaCall - std::exp(-q * T);
		return delta;
	}

	// Unassigend
	template < class O, class R>
	double StandardBlackScholes< ql::PutCallT::Unassigned, O, R >::premium()
	{
		throw Assert::Error(Assert::compose(__FILE__,__LINE__, "To compute premium, Put or Call should be assigned"));
	}

	template <class O, class R >
	double StandardBlackScholes< ql::PutCallT::Unassigned, O, R  >::delta()
	{
		throw Assert::Error(Assert::compose(__FILE__, __LINE__, "To compute delta, Put or Call should be assigned"));
	}


}

