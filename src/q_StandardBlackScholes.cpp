#include "StandardBlackScholes.h"
#include "q_StandardBlackScholes.h"

double // Call and Put price with standar log-normal Black-Scholes model
q_StandarBlackScholes(double spot // spot
, double strike // strike
, double tipoInteres //  tipoInteres
, double FechaValor //  FechaValor
, double FechaVcto // FechaVcto
, double Volatilidad // Volatilidad
, double Dividendos // Dividendos 
, bool Call // true for Call, false for Put
)
{
	return ql::IStandardBlackScholes(spot, strike, tipoInteres, FechaValor, FechaVcto, Volatilidad, Dividendos, true);
}

