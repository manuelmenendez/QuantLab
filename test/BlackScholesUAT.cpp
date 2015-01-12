#include <gtest/gtest.h>
#include "BlackScholesUAT.h"
#include "TestBasicOptionFixedValues.h"

#define protected public
#define private   public
#include "BasicOption.h"
#include "BasicOption.cpp"
#include "StandardBlackScholes.h"
#include "StandardBlackScholes.cpp"
#undef protected
#undef private

void BlackScholesUATFixture::SetUp()
{
	option_ = test::TestBasicOptionFixedValues();
};


TEST_F(BlackScholesUATFixture, positive_call) {

	//These case tests typical values
	ql::StandardBlackScholes<> myB(*option_);

	EXPECT_NEAR(0.0164777110308015, myB.d1(), ql::StandardBlackScholes<>::eps);
	EXPECT_NEAR(-0.33464573055759, myB.d2(), ql::StandardBlackScholes<>::eps);
	EXPECT_NEAR(0.506573358152231, myB.nd1(), ql::StandardBlackScholes<>::eps);
	EXPECT_NEAR(0.398888124678723, myB.ndd1(), ql::StandardBlackScholes<>::eps);
}


TEST_F(BlackScholesUATFixture, testPremium) {
	
	ql::StandardBlackScholes<> myB(*option_);
	EXPECT_NEAR(0.109741780719115, myB.premium(), ql::StandardBlackScholes<>::eps);
}

