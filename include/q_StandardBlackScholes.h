
#ifndef Q_STANDARDBLACKSCHOLES_H
#define Q_STANDARDBLACKSCHOLES_H

//<xlw:libraryname=QuantLab


double // Call and Put price with standar log-normal Black-Scholes model
q_StandarBlackScholes(double spot // spot
    , double strike // strike
	, double interestRate //  Interest Rate
	, double valueDate //  Value date
	, double expiryDtae // Expiry
	, double volatility // Volatility
	, double Dividends // Dividends
	, bool isCall // true for Call, false for Put
	);


#endif
