#include <gtest/gtest.h>
#include "BlackScholesUT.h"

// Do not this in production code. It is only an example of testing private members, which should not be neccesary
#define protected public
#define private   public
#include "BasicOption.h"
#include "BasicOption.cpp"
#include "StandardBlackScholes.h"
#include "StandardBlackScholes.cpp"
#undef protected
#undef private


void BlackScholesOptionUTFixture::SetUp()
{
	option_.Spot(1.0);
	option_.Strike(1.1);
	option_.InterestRate(0.05);
	option_.ValueDate(42003);
	option_.Expiry(42723);
	option_.Volatility(0.25);
	option_.Dividends(0.3);
	option_.PutCall(ql::PutCallT::Call);
	option_.Dividends(0.3);
};
	

TEST_F(BlackScholesOptionUTFixture, testd1) {

	option_.Spot(0.95);
	option_.Strike(1.05);
	option_.InterestRate(0.08);
	option_.ValueDate(42009);
	option_.ValueDate(42723);

	ql::StandardBlackScholes <> myBlackScholes(option_);

#pragma message("Comparacion de flotantes, por favor!!")
	EXPECT_EQ(11.0867808943643, myBlackScholes.d1());
}

TEST_F(BlackScholesOptionUTFixture, testPositive) {

	ql::StandardBlackScholes<ql::BasicOption<>>  myBlackScholes(option());

#pragma message("Comparacion de flotantes, por favor!!")
	EXPECT_EQ(11.0867808943643, myBlackScholes.premium()); 
}

