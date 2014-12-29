
#ifndef STANDARDBLACKSCHOLES_H
#define STANDARDBLACKSCHOLES_H

// typedef double Date;
//typedef bool IsCall;


double // Call and Put price with standar log-normal Black-Scholes model
StandardBlackScholes(double spot // spot
    , double strike // strike
	, double tipoInteres //  tipoInteres
	, double FechaValor //  FechaValor
	, double FechaVcto // FechaVcto
	, double Volatilidad // Volatilidad
	, double Dividendos // Dividendos 
	, bool Call // true for Call, false for Put
	);



#endif
