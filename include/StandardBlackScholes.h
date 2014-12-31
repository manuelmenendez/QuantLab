
#ifndef STANDARDBLACKSCHOLES_H
#define STANDARDBLACKSCHOLES_H

namespace ql {


	//"C" Interface
	double IStandardBlackScholes(double spot,  double strike , double interestRate , long valueDate , long expiry ,
		double volatility , double dividends , bool IsCall );

	template < class O >
	class StandardBlackScholes
	{
	public:
		StandardBlackScholes(const O & option) : theOption_(option) {}
		double premium();

	private:
		O theOption_;
	};

} //namespace
#endif
