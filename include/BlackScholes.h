#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

typedef double Date ;
typedef bool IsCall ;

double q_EstandarBlackScholes(
	double spot,
	double strike,
	double tipoInteres,
	Date FechaValor,
	Date FechaVcto,
	double Volatilidad,
	double Dividendos,
	IsCall IsCall);


#endif
