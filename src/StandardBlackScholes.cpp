#include <cmath>
#include <limits>

#include <boost/math/distributions/normal.hpp>

#include "DynamicAssert.h"
#include "StandardBlackScholes.h"
#include "BasicOption.h"

namespace ql
{
	template StandardBlackScholes<ql::BasicOption<double, double, double, double> >;

	double IStandardBlackScholes(
		double spot,
		double strike,
		double interestRate,
		long valueDate,
		long expiry,
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
		
		const double T = theOption_.yearFractionToExpiry();
		const double factor = exp(-r * T);
		double premium = (exp(-q*T) * S * nd1() - K * factor * nd2());
		return  premium;
	}

	template < class O >
	double StandardBlackScholes< O >::d1()
	{
		const  O::PriceT S = theOption_.Spot();
		const  O::PriceT K = theOption_.Strike();
		const  O::InterestT r = theOption_.InterestRate();
		const  O::DividendT q = theOption_.Dividends();
		const  O::VolatillityT SIG = theOption_.Volatility();
		const double T = theOption_.yearFractionToExpiry();
		
		const double eps = std::numeric_limits<double>::epsilon() * 100.0;

	/*	Assert::dynamic( ( std::abs(K) < eps  ), Assert::compose(__FILE__, __LINE__, "K is zero"));
		Assert::dynamic( ( S / K < eps), Assert::compose(__FILE__, __LINE__, "S/K is negative"));
		Assert::dynamic( ( S / K < eps), Assert::compose(__FILE__, __LINE__, "S/K is negative"));
		*/

		return  (std::log(S / K) + (r - q + 0.5 * SIG * SIG)* T) / (SIG * std::sqrt(T));
	}

	template < class O >
	double StandardBlackScholes< O>::d2()
	{
		const O::VolatillityT SIG = theOption_.Volatility();
		const double T = theOption_.yearFractionToExpiry();
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

