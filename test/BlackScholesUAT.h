#ifndef BLACKSCHOLESUT_H
#define BLACKSCHOLESUT_H

#include "BasicOption.h"
#include "StandardBlackScholes.h"


class BlackScholesUATFixture : public ::testing::Test
{
	public:
		BlackScholesUATFixture() : option_() {}
		const ql::BasicOption<>  & option() { return option_; }
		ql::BasicOption<> option_;
	
	protected:
		 virtual void	SetUp();

		
};





#endif