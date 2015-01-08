#ifndef BASICOPTION_H
#define BASICOPTION_H


#include "Date.h"

namespace ql {
	

	enum  class PutCallT{ Put, Call, Unassigned };

	//Class that represents a standard BlackScholes Option. Altough usually instatiated with simple types
	//it is templatized to be able to  use more complex types for V, prices etc...
	// Semantic of measures is parts per unit.
	
	template < class P = double, class I = double, class VT = double, class D = double>
	class BasicOption 
	{
	public:


		BasicOption() : spot_(0), strike_(0), interestRate_(0), valueDate_(0), expiry_(0), volatility_(0),
			dividends_(0), putCall_(PutCallT::Unassigned){}
		
		BasicOption(const P & spot,
			const P & strike,
			const I & interestRate,
			const Date & valueDate,
			const Date & expiry,
			const VT & V,
			const D & dividends,
			const PutCallT & putCall) : spot_(spot), strike_(strike), interestRate_(interestRate), 
										valueDate_(valueDate), expiry_(expiry), V_(V),
										dividends_(dividends), putCall_(putCall){}

		const P & Spot() const  { return spot_; }
		void Spot(const P & spot) { spot_ = spot; }

		const P & Strike() const { return strike_; };
		void Strike(const P & strike) { strike_ = strike; }
		
		const I & InterestRate() const { return interestRate_; }
		void InterestRate(const I & interestRate) { interestRate_= interestRate; }

		const Date & ValueDate() const { return valueDate_; }
		void ValueDate(const Date & valueDate) { valueDate_ = valueDate; }

		const Date & Expiry() const { return expiry_; }

		void Expiry(const Date & expiry) { expiry_ = expiry; }

		const VT & Volatility() const { return volatility_; }
		void Volatility(const VT & V) { volatility_ = V; }

		const D & Dividends() const { return dividends_; }
		void Dividends(const D & dividends) { dividends_ = dividends; }

		const PutCallT & PutCall() const { return putCall_; }
		void PutCall(const PutCallT & putCall) { putCall_ = putCall; }

		double yearFractionToExpiry() const;

		
	private:
		P spot_;
		P strike_;
		I interestRate_;
		Date valueDate_;
		Date expiry_;
		VT volatility_;
		D dividends_;
		PutCallT putCall_;
	};


} // namespace
#endif

