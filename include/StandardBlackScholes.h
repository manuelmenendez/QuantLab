
#ifndef STANDARDBLACKSCHOLES_H
#define STANDARDBLACKSCHOLES_H

#include "BasicOption.h"

namespace ql {


	//"C" Interface
	double IStandardBlackScholes(double spot, double strike, double interestRate, double valueDate, double expiry,
		double volatility, double dividends, bool IsCall );

	template <  class O = BasicOption<> >
	class StandardBlackScholes
	{

	public:
		StandardBlackScholes(const O & option) : theOption_(option) {}
		double premium();
		void evaluate(double & premium, double & delta, double & gamma, double & vega){}
		static const double eps;

	private:
		double d1();
		double d2();
		double nd1();
		double ndd1();
		double nd2();
		O  theOption_;
	};

} //namespace ql




#endif
