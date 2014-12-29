
#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

// typedef double Date;
//typedef bool IsCall;



//#include "xlw/MyContainers.h"
//#include <xlw/CellMatrix.h>
//#include <xlw/DoubleOrNothing.h>
//#include <xlw/ArgList.h>
//#include "reftest.h"

//using namespace xlw;


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
