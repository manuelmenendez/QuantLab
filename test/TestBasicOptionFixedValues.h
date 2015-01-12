#ifndef TESTBASICOPTIONFIXEDVALUES_H
#define TESTBASICOPTIONFIXEDVALUES_H


#include <memory>
#include "BasicOption.h"

namespace test{

	inline
	std::unique_ptr<ql::BasicOption<>> TestBasicOptionFixedValues()
	{
		std::unique_ptr<ql::BasicOption<>> ret = std::make_unique<ql::BasicOption<>>();
		ret->Spot(1.0);
		ret->Strike(1.1);
		ret->InterestRate(0.05);
		ret->ValueDate(42003);
		ret->Expiry(42723);
		ret->Volatility(0.25);
		ret->Dividends(0.03);
		ret->PutCall(ql::PutCallT::Call);
		ret->Dividends(0.03);

		return ret;
	}

}

#endif