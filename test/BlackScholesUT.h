#ifndef BLACKSCHOLESUT_H
#define BLACKSCHOLESUT_H

#include "BasicOption.h"


class BlackScholesOptionFixture : public ::testing::Test
{
	public:
		BlackScholesOptionFixture() : option_() {}
		const ql::BasicOption<>  & option() { return option_; }
	protected:
		virtual void	SetUp();
	private:
		ql::BasicOption<> option_;
};



#endif