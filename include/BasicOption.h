#ifndef BASICOPTION_H
#define BASICOPTION_H


#include "Date.h"

namespace ql {
	

	enum  class PutCallT{ Put, Call, Unassigned };

	//Class that represents a standard BlackScholes Option. Altough usually instatiated with simple types
	//it is templatized to be able to  use more complex types for V, prices etc...
	// Semantic of measures is parts per unit.
	
	template < typename P = double, typename I = double, typename VT = double, typename D = double>
	class BasicOption 
	{
	public:
		using  PriceT = P;
		using  InterestT = I;
		using  VolatillityT = VT;
		using  DividendT = D;
		
		static const double eps;

		BasicOption() : spot_(0), strike_(0), interestRate_(0), valueDate_(0), expiry_(0), volatility_(0),
			dividends_(0), putCall_(PutCallT::Unassigned){}
		
		BasicOption(const PriceT & spot,
			const PriceT & strike,
			const InterestT & interestRate,
			const Date & valueDate,
			const Date & expiry,
			const VolatillityT & V,
			const DividendT & dividends,
			const PutCallT & putCall) : spot_(spot), strike_(strike), interestRate_(interestRate), 
										valueDate_(valueDate), expiry_(expiry), volatility_(V),
										dividends_(dividends), putCall_(putCall){}

		const PriceT & Spot() const  { return spot_; }
		void Spot(const PriceT & spot) { spot_ = spot; }

		const PriceT & Strike() const { return strike_; };
		void Strike(const PriceT & strike) { strike_ = strike; }
		
		const InterestT& InterestRate() const { return interestRate_; }
		void InterestRate(const InterestT & interestRate) { interestRate_= interestRate; }

		const Date & ValueDate() const { return valueDate_; }
		void ValueDate(const Date & valueDate) { valueDate_ = valueDate; }

		const Date & Expiry() const { return expiry_; }

		void Expiry(const Date & expiry) { expiry_ = expiry; }

		const VolatillityT & Volatility() const { return volatility_; }
		void Volatility(const VolatillityT & V) { volatility_ = V; }

		const DividendT & Dividends() const { return dividends_; }
		void Dividends(const DividendT & dividends) { dividends_ = dividends; }

		const PutCallT & PutCall() const { return putCall_; }
		void PutCall(const PutCallT & putCall) { putCall_ = putCall; }

		double YearFractionToExpiry() const;

		
	private:
		PriceT spot_;
		PriceT strike_;
		InterestT interestRate_;
		Date valueDate_;
		Date expiry_;
		VolatillityT volatility_;
		DividendT dividends_;
		PutCallT putCall_;
	};


} // namespace
#endif

