#include <gtest/gtest.h>
#include "TestBasicOptionFixedValues.h"
#include "Exchange.h"
#include "BlackScholesUT.h"
#include "Date.h"

// Do not redefine keywords in production code. It is only a technique for testing private members, which should not be neccesary
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
	option_ = test::TestBasicOptionFixedValues();
};
	


TEST_F(BlackScholesOptionUTFixture, testPremium) {

	ql::StandardBlackScholes<> myB(*option_);
	EXPECT_NEAR(0.109741780719115, myB.premium(), ql::StandardBlackScholes<>::eps);
}

TEST_F(BlackScholesOptionUTFixture, testAsserts) {

	ql::StandardBlackScholes<> myB(*option_);

	ASSERT_EQ(Assert::current_mode, Assert::Mode::throw_);

	test::EX <ql::BasicOption<>, double>( option_.get(),
										&ql::BasicOption<>::Expiry, //Setter from
										&ql::BasicOption<>::Expiry,  //Getter from
										&ql::BasicOption<>::ValueDate, //Setter to
										&ql::BasicOption<>::ValueDate); // Getter to
	
	
	
	
	//EXPECT_THROW( myB.premium(), Assert::Error);


}