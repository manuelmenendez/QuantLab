#ifndef BASICOPTION_H
#define BASICOPTION_H


#include "Date.h"

namespace ql {
	

	enum  class PutCallT{ Put, Call, Unassigned };

	//Class that represents a standard BlackScholes Option. Altough usually instatiated with simple types
	//it is templatized to be able to  use more complex types for V, prices etc...
	
	//Semantic of measures is parts per unit.
	
	template < typename P = double, typename I = double, typename VT = double, typename D = double>
	class BasicOption 
	{
	public:
		using  PriceT = P;
		using  InterestT = I;
		using  VolatillityT = VT;
		using  DividendT = D;
		
		static const double eps;

		BasicOption() = default;
		
		BasicOption(const PriceT & spot,
			const PriceT & strike,
			const InterestT & interestRate,
			const Date & valueDate,
			const Date & expiry,
			const VolatillityT & V,
			const DividendT & dividends,
			const PutCallT & putCall) : spot_(spot), strike_(strike), interestRate_(interestRate),
			valueDate_(valueDate), expiry_(expiry), volatility_(V),
			dividends_(dividends), putCall_(putCall) {};

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
		PriceT spot_ = PriceT(0);
		PriceT strike_ = PriceT(0);
		InterestT interestRate_ = InterestT(0);
		Date valueDate_ = Date(0);
		Date expiry_ = Date(0);
		VolatillityT volatility_ = VolatillityT(0);
		DividendT dividends_ = DividendT(0);
		PutCallT putCall_ = PutCallT::Unassigned;
	};


} // namespace
#endif

