#include "StandardBlackScholes.h"
#include "q_StandardBlackScholes.h"

#pragma message("*** MGP: Investigar como leer fechas desde Excel")
double // Call and Put price with standar log-normal Black-Scholes model
q_StandarBlackScholes(double spot // spot
					, double strike // strike
					, double interestRate //  Interest Rate
					, double valueDate //  Value date
					, double expiryDtae // Expiry
					, double volatility // Volatility
					, double Dividends // Dividends
					, bool isCall // true for Call, false for Put
)
{
	return IStandardBlackScholes(spot, strike, interestRate, valueDate, expiryDtae, volatility, Dividends, isCall);
}
