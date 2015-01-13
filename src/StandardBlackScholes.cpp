#include <cmath>
#include <limits>

#include <boost/math/distributions/normal.hpp>

#include "DynamicAssert.h"
#include "StandardBlackScholes.h"
#include "BasicOption.h"

namespace ql
{
	template <class O = ql::BasicOption<>>
	const double StandardBlackScholes<O>::eps = 10e-12;

	template StandardBlackScholes<ql::BasicOption <double, double, double, double> >;

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

		StandardBlackScholes<> myBlackScholes(myOption);
		return myBlackScholes.premium();
	}

	template < class O >
	double StandardBlackScholes< O >::premium()
	{
		const  O::PriceT S = theOption_.Spot();
		const  O::PriceT K = theOption_.Strike();
		const  O::InterestT r = theOption_.InterestRate();
		const  O::DividendT q = theOption_.Dividends();
		const  O::VolatillityT SIG = theOption_.Volatility();
		
		const double T = theOption_.YearFractionToExpiry();

		Assert::dynamic((-r * T < StandardBlackScholes::eps), Assert::compose(__FILE__, __LINE__, "-r * T is below zero"));

		const double factor = exp(-r * T);
		double premium = (exp(-q*T) * S * nd1() - K * factor * nd2());
		return  premium;
	}

	template < class O >
	double StandardBlackScholes< O >::d1()
	{
		using namespace Assert;

		const  O::PriceT S = theOption_.Spot();
		const  O::PriceT K = theOption_.Strike();
		const  O::InterestT r = theOption_.InterestRate();
		const  O::DividendT q = theOption_.Dividends();
		const  O::VolatillityT SIG = theOption_.Volatility();
		const double T = theOption_.YearFractionToExpiry();

		dynamic_release( ( std::abs(K) > StandardBlackScholes::eps  ), compose(__FILE__, __LINE__, "K is zero"));
		dynamic_release( (S / K > StandardBlackScholes::eps), compose(__FILE__, __LINE__, "S/K is negative"));
		dynamic_release( (T > StandardBlackScholes::eps), compose(__FILE__, __LINE__, "T is negative"));

		double d1 = (std::log(S / K) + (r - q + 0.5 * SIG * SIG)* T) / (SIG * std::sqrt(T));
		return  d1;
	}

	template < class O >
	double StandardBlackScholes< O>::d2()
	{
		using namespace Assert;
		const O::VolatillityT SIG = theOption_.Volatility();
		const double T = theOption_.YearFractionToExpiry();

		dynamic_release( (T > StandardBlackScholes::eps), compose(__FILE__, __LINE__, "T is negative"));
		
		const double d2 = (d1() - SIG * std::sqrt(T));
		return d2;
	}

	template < class O >
	double StandardBlackScholes< O>::nd1()
	{
		const boost::math::normal_distribution<> nd1(0.0, 1.0);
		const double cdf = boost::math::cdf<>(nd1, d1());
		return cdf;
	}

	template < class O >
	double StandardBlackScholes< O >::ndd1()
	{
		const boost::math::normal_distribution<> nd1(0.0, 1.0);
		double pdf = boost::math::pdf<>(nd1, d1());
		return pdf;
	}

	template < class O >
	double StandardBlackScholes< O >::nd2()
	{
		boost::math::normal_distribution<> nd1(0.0, 1.0);
		double cdf = boost::math::cdf<>(nd1, d2());
		return cdf;
	}

}

