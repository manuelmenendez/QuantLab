#include <cmath>
#include <limits>

#include <boost/math/distributions/normal.hpp>

#include "DynamicAssert.h"
#include "StandardBlackScholes.h"
#include "BasicOption.h"

namespace ql
{
	template StandardBlackScholes<ql::BasicOption<double, double, double, double>, double, double, double, double>;

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

	template < class O, class P, class I, class VT, class D >
	double StandardBlackScholes< O, P, I, VT, D>::premium()
	{
		P S = theOption_.Spot();
		P K = theOption_.Strike();
		I r = theOption_.InterestRate();
		D q = theOption_.Dividends();
		VT SIG = theOption_.Volatility();
		
		double T = theOption_.yearFractionToExpiry();
		double factor = exp(-r * T);
		double premium = (exp(-q*T) * S * nd1() - K * factor * nd2());
		return  premium;
	}

	template < class O, class P, class I, class VT, class D >
	double StandardBlackScholes< O, P, I, VT, D>::d1()
	{
		const P S = theOption_.Spot();
		const P K = theOption_.Strike();
		const I r = theOption_.InterestRate();
		const D q = theOption_.Dividends();
		const VT SIG = theOption_.Volatility();
		const double T = theOption_.yearFractionToExpiry();
		
		const double eps = std::numeric_limits<double>::epsilon() * 100.0;

	/*	Assert::dynamic( ( std::abs(K) < eps  ), Assert::compose(__FILE__, __LINE__, "K is zero"));
		Assert::dynamic( ( S / K < eps), Assert::compose(__FILE__, __LINE__, "S/K is negative"));
		Assert::dynamic( ( S / K < eps), Assert::compose(__FILE__, __LINE__, "S/K is negative"));
		*/

		return  (std::log(S / K) + (r - q + 0.5 * SIG * SIG)* T) / (SIG * std::sqrt(T));
	}

	template < class O, class P, class I, class VT, class D>
	double StandardBlackScholes< O, P, I, VT, D>::d2()
	{
		VT SIG = theOption_.Volatility();
		double T = theOption_.yearFractionToExpiry();
		double d2 = (d1() - SIG * std::sqrt(T));
		return d2;
	}

	template < class O, class P, class I, class VT, class D>
	double StandardBlackScholes< O, P, I, VT, D>::nd1()
	{
		boost::math::normal_distribution<> nd1(0.0, 1.0);
		double cdf = boost::math::cdf<>(nd1, d1());
		return cdf;
	}

	template < class O, class P, class I, class VT, class D>
	double StandardBlackScholes< O, P, I, VT, D>::ndd1()
	{
		boost::math::normal_distribution<> nd1(0.0, 1.0);
		double pdf = boost::math::pdf<>(nd1, d1());
		return pdf;
	}

	template < class O, class P, class I, class VT, class D>
	double StandardBlackScholes< O, P, I, VT, D>::nd2()
	{
		boost::math::normal_distribution<> nd1(0.0, 1.0);
		double cdf = boost::math::cdf<>(nd1, d2());
		return cdf;
	}


}

