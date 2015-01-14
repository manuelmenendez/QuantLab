#ifndef TESTBASICOPTIONFIXEDVALUES_H
#define TESTBASICOPTIONFIXEDVALUES_H


#include <memory>
#include "BasicOption.h"

namespace test{

	inline
	void fillBasicOption( ql::BasicOption<> & ret )
	{
		ret.Spot(1.0);
		ret.Strike(1.1);
		ret.InterestRate(0.05);
		ret.ValueDate(42003);
		ret.Expiry(42723);
		ret.Volatility(0.25);
		ret.Dividends(0.03);
		ret.Dividends(0.03);
	}

	template <const ql::PutCallT> inline
	std::unique_ptr<ql::BasicOption<>> TestBasicOptionFixedValues();

	template <> inline
	std::unique_ptr<ql::BasicOption<>> TestBasicOptionFixedValues <ql::PutCallT::Call>()
	{
		std::unique_ptr<ql::BasicOption<>> ret = std::make_unique<ql::BasicOption<>>();
		fillBasicOption(*ret);
		ret->PutCall(ql::PutCallT::Call);
		return ret;
	}

	template <> inline
	std::unique_ptr<ql::BasicOption<>> TestBasicOptionFixedValues <ql::PutCallT::Put>()
	{
		std::unique_ptr<ql::BasicOption<>> ret = std::make_unique <ql::BasicOption<>>();
		fillBasicOption(*ret);
		ret->PutCall(ql::PutCallT::Put);
		return ret;
	}
}

#endif