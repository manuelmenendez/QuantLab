
#ifndef Q_STANDARDBLACKSCHOLES_H
#define Q_STANDARDBLACKSCHOLES_H

//<xlw:libraryname=QuantLab


double // Call and Put price with standar log-normal Black-Scholes model
q_StandarBlackScholes(double spot // spot
    , double strike // strike
	, double tipoInteres //  tipoInteres
	, double FechaValor //  FechaValor
	, double FechaVcto // FechaVcto
	, double Volatilidad // Volatilidad
	, double Dividendos // Dividendos 
	, bool Call // true for Call, false for Put
	);


#endif
