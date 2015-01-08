
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
		double nd1();
		double ndd1();
		double nd2();
		O  theOption_;
	};

	//template <ql::PutCallT N = ql::PutCallT::Call, class O = BasicOption<>, class P = double, class I = double, class VT = double, class D = double >
	//double Premium_imp();


	template <ql::PutCallT N > double test();
	template <class C, ql::PutCallT N > double test2();
} //namespace ql




#endif
