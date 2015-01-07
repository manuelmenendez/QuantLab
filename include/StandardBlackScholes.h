
#ifndef STANDARDBLACKSCHOLES_H
#define STANDARDBLACKSCHOLES_H

#include "BasicOption.h"

namespace ql {


	//"C" Interface
	double IStandardBlackScholes(double spot,  double strike , double interestRate , long valueDate , long expiry ,
		double volatility , double dividends , bool IsCall );


	template <  class O = BasicOption<>, class P = double, class I = double, class VT = double, class D = double >
	class StandardBlackScholes
	{
	public:
		StandardBlackScholes(const O & option) : theOption_(option) {}
		double premium();
		
	private:
		double d1();
		double d2();

		O  theOption_;
	};

} //namespace
#endif
