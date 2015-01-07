#include <cmath>
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

		return myOption.Spot();
	}

	template < class O, class P, class I, class VT, class D >
	double StandardBlackScholes< O, P, I, VT, D>::premium()
	{
		return -1.0f;
	}
	
	template < class O, class P, class I, class VT, class D >
	double StandardBlackScholes< O, P, I, VT, D>::d1()
	{
		P S = theOption_.Spot();
		P K = theOption_.Strike();
		I r = theOption_.InterestRate();
		D q = theOption_.Dividends();
		VT SIG = theOption_.Volatility();
		double T = theOption_.yearFractionToExpiry();

		return  (std::log(S / K) + (r - q + 0.5 * std::exp(SIG * SIG) * T) / (SIG * std::sqrt(T)));
	}

	
	
	template < class O, class P, class I, class VT, class D> 
	double StandardBlackScholes< O, P, I, VT, D>::d2()
	{
		VT SIG = theOption_.Volatility();
		double T = theOption_.yearFractionToExpiry();

		return (d1() - SIG * std::sqrt(T));
	}

	
}