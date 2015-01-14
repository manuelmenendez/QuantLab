
#ifndef STANDARDBLACKSCHOLES_H
#define STANDARDBLACKSCHOLES_H

#include <memory>
#include "BasicOption.h"
#include "Result.h"

//"C" Interface
extern "C" double IStandardBlackScholes ( double spot, double strike, double interestRate, double valueDate, double expiry,
											double volatility, double dividends, bool IsCall);


namespace ql {
	// this class should not be instatiated. Instead use one of the specialized templates. Example
#pragma message("Corregir este comentario")

	template < const ql::PutCallT P = ql::PutCallT::Unassigned, typename O = ql::BasicOption<>, typename R = ql::Result<> >
	class StandardBlackScholes_BASE
	{
	public:
		virtual double premium() = 0;
		virtual double delta() = 0;
		double vega(); 
		double gamma();
		static double eps();
		
	protected:
		StandardBlackScholes_BASE(const O & option) : theOption_(option) {};
		double d1();
		double d2();
		double nd1();
		double ndd1();
		double nd2();
	    const O &  theOption_;
	};

	template < const ql::PutCallT  P = ql::PutCallT::Unassigned, typename O = ql::BasicOption<>, typename R = ql::Result<> >
	class StandardBlackScholes : public StandardBlackScholes_BASE<P,O,R>
	{
	};

	template <typename O, typename R>
	class StandardBlackScholes < ql::PutCallT::Put, O, R > : public StandardBlackScholes_BASE<ql::PutCallT::Put, O, R>
	{
	public:
		StandardBlackScholes(const O & option) : StandardBlackScholes_BASE<ql::PutCallT::Put, O, R>(option) {}
		double premium();
		double delta();
	};

	template <typename O, typename R>
	class StandardBlackScholes < ql::PutCallT::Call, O, R > : public StandardBlackScholes_BASE<ql::PutCallT::Call, O, R>
	{
	public:
		StandardBlackScholes(const O & option) : StandardBlackScholes_BASE<ql::PutCallT::Call, O, R>(option) {}
		double premium();
		double delta();
	
	};

	template <typename O, typename R>
	class StandardBlackScholes < ql::PutCallT::Unassigned, O, R > : public StandardBlackScholes_BASE<ql::PutCallT::Call, O, R>
	{
	public:
		StandardBlackScholes(const O & option) : StandardBlackScholes_BASE<ql::PutCallT::Call, O, R>(option) {}
		double premium();
		double delta();

	};

} //namespace ql


#endif
