#include <gtest/gtest.h>

#include "BasicOption.h"
#include "BasicOptionUAT.h"
#include "TestBasicOptionFixedValues.h"



void BasicOptionOptionUATFixture::SetUp()
{
	option_ = test::TestBasicOptionFixedValues();
};


TEST_F(BasicOptionOptionUATFixture, checkYearFractionToExpiry) {

	EXPECT_NEAR(1.97260273972603, option_->YearFractionToExpiry(), ql::BasicOption<>::eps);
}

