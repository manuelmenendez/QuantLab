#include "BlackScholes.h"

double q_EstandarBlackScholes(
	double spot,
	double strike,
	double tipoInteres,
	double FechaValor,
	double FechaVcto,
	double Volatilidad,
	double Dividendos,
	bool Call)
{
	return spot + strike + tipoInteres + FechaValor + FechaValor + FechaVcto + Volatilidad + Dividendos + Call;
}
