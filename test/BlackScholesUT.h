#ifndef BLACKSCHOLESUT_H
#define BLACKSCHOLESUT_H

#include "BasicOption.h"


class BlackScholesOptionUTFixture : public ::testing::Test
{
public:
	BlackScholesOptionUTFixture() : option_() {}
	const ql::BasicOption<>  & option() { return option_; }
	ql::BasicOption<> option_;
	static const double epsilon;
protected:
	virtual void	SetUp();

};


#endif