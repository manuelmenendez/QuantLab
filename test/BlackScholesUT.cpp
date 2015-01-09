#include <gtest/gtest.h>
#include "BlackScholesUT.h"

// Do not redefine keywords in production code. It is only a technique for testing private members, which should not be neccesary
#define protected public
#define private   public
#include "BasicOption.h"
#include "BasicOption.cpp"
#include "StandardBlackScholes.h"
#include "StandardBlackScholes.cpp"
#undef protected
#undef private

const double BlackScholesOptionUTFixture::epsilon = 1E-15;

void BlackScholesOptionUTFixture::SetUp()
{
	option_.Spot(1.0);
	option_.Strike(1.1);
	option_.InterestRate(0.05);
	option_.ValueDate(42003);
	option_.Expiry(42723);
	option_.Volatility(0.25);
	option_.Dividends(0.03);
	option_.PutCall(ql::PutCallT::Call);
};
	

TEST_F(BlackScholesOptionUTFixture, positive_call) {

	//These case tests typical values
	ql::StandardBlackScholes <> myBlackScholes(option_);

	EXPECT_NEAR(0.0164777110308015, myBlackScholes.d1(),      BlackScholesOptionUTFixture::epsilon);
	EXPECT_NEAR(-0.33464573055759,  myBlackScholes.d2(),      BlackScholesOptionUTFixture::epsilon);
	EXPECT_NEAR(0.506573358152231,  myBlackScholes.nd1(),     BlackScholesOptionUTFixture::epsilon);
	EXPECT_NEAR(0.398888124678723,  myBlackScholes.ndd1(),    BlackScholesOptionUTFixture::epsilon);
	EXPECT_NEAR(0.109741780719115,  myBlackScholes.premium(), BlackScholesOptionUTFixture::epsilon);
}

