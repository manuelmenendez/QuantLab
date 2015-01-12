#ifndef BLACKSCHOLESUT_H
#define BLACKSCHOLESUT_H
#include <memory>
#include <gtest/gtest.h>
#include "BasicOption.h"


class BlackScholesUATFixture : public ::testing::Test
{
	public:
		BlackScholesUATFixture() : option_() {}
		std::unique_ptr<ql::BasicOption<>> option_;
	
	protected:
		 virtual void	SetUp();

};


#endif