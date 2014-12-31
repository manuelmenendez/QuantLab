#include <gtest/gtest.h>
#include "StandardBlackScholes.h"
#include "BlackScholesUT.h"

void BlackScholesOptionFixture::SetUp()
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
	

TEST_F(BlackScholesOptionFixture, testPositive) {

	ql::StandardBlackScholes<ql::BasicOption<>>  myBlackScholes(option());

#pragma message("Comparacion de flotantes, por favor!!")
	EXPECT_EQ(11.0867808943643, myBlackScholes.premium()); 
}

