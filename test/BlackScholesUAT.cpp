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
	option_ = test::TestBasicOptionFixedValues<ql::PutCallT::Call>();
};


TEST_F(BlackScholesUATFixture, positive_call) {

	//These case tests typical values
	ql::StandardBlackScholes<> myB(*option_);

	EXPECT_NEAR(0.0164777110308015, myB.d1(),   ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(-0.33464573055759,  myB.d2(),   ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(0.506573358152231,  myB.nd1(),  ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(0.398888124678723,  myB.ndd1(), ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesUATFixture, testPremium_call) {
	
	ql::StandardBlackScholes<ql::PutCallT::Call > myB(*option_);
	EXPECT_NEAR(0.109741780719115, myB.premium(), ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesUATFixture, testGreeks_call) {

	ql::StandardBlackScholes<ql::PutCallT::Call > myB(*option_);
	EXPECT_NEAR(0.477465098202127, myB.delta(),		ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(1.07075612633066, myB.gamma(),	ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(0.52804411709457, myB.vega(),		ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesUATFixture, testPremium_put) {
	option_->PutCall(ql::PutCallT::Put);
	ql::StandardBlackScholes<ql::PutCallT::Put > myB(*option_);
	EXPECT_NEAR(0.163888423684506, myB.premium(), ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesUATFixture, testGreeks_put) {

	option_->PutCall(ql::PutCallT::Put);
	ql::StandardBlackScholes<ql::PutCallT::Put > myB(*option_);
	EXPECT_NEAR(-0.465073806614583, myB.delta(),	ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(1.07075612633066, myB.gamma(),	ql::StandardBlackScholes<>::eps());
	EXPECT_NEAR(0.52804411709457, myB.vega(),		ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesUATFixture, test_unassigned) {

	ql::StandardBlackScholes<> myB(*option_);
	EXPECT_THROW(myB.premium(), Assert::Error);
	EXPECT_THROW(myB.delta(),	Assert::Error);
	EXPECT_NO_THROW(myB.gamma());
	EXPECT_NO_THROW(myB.vega());
}

