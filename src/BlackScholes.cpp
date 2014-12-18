#include "BlackScholes.h"

double q_EstandarBlackScholes(
	double spot,
	double strike,
	double tipoInteres,
	Date FechaValor,
	Date FechaVcto,
	double Volatilidad,
	double Dividendos,
	IsCall Call)
{
	return spot + strike + tipoInteres + FechaValor + FechaValor + FechaVcto + Volatilidad + Dividendos + Call;
}

