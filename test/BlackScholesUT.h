#ifndef BLACKSCHOLESUT_H
#define BLACKSCHOLESUT_H

#include <gtest/gtest.h>
#include "BasicOption.h"


class BlackScholesOptionUTFixture : public ::testing::Test
{
public:
	BlackScholesOptionUTFixture() : option_() {}
	std::unique_ptr<ql::BasicOption<>> option_;

protected:
	virtual void	SetUp();

};


#endif