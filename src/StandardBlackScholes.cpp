#include "StandardBlackScholes.h"
#include "BasicOption.h"

namespace ql
{

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


	template <typename O>
	double StandardBlackScholes<O>::premium()
	{
		return -1.0f;
	}



	template class StandardBlackScholes <BasicOption<double, double, double, double>>;
}