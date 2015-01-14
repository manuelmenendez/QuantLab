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
	option_ = test::TestBasicOptionFixedValues<ql::PutCallT::Call>();
};
	
TEST_F(BlackScholesOptionUTFixture, testPremium) {

	ql::StandardBlackScholes<ql::PutCallT::Call> myB(*option_);
	EXPECT_NEAR(0.109741780719115, myB.premium(), ql::StandardBlackScholes<>::eps());
}

TEST_F(BlackScholesOptionUTFixture, testExchange ){


	ASSERT_EQ(Assert::current_mode, Assert::Mode::throw_);

	test::Exchange<ql::BasicOption<>, double>( option_.get(),
										&ql::BasicOption<>::Expiry, //Setter from
										&ql::BasicOption<>::Expiry,  //Getter from
										&ql::BasicOption<>::ValueDate, //Setter to
										&ql::BasicOption<>::ValueDate); // Getter to
	
	std::unique_ptr<ql::BasicOption<>> option2 = test::TestBasicOptionFixedValues<ql::PutCallT::Call>();
	
	EXPECT_EQ(option_->Expiry(), option2->ValueDate());

	EXPECT_EQ(option2->Expiry(), option_->ValueDate());

	std::unique_ptr<ql::BasicOption<>> option3 = test::TestBasicOptionFixedValues<ql::PutCallT::Call>();

	test::Exchange<ql::BasicOption<>, ql::BasicOption<>, double>(option2.get(), option3.get(),
		&ql::BasicOption<>::Expiry, //Setter object1
		&ql::BasicOption<>::ValueDate,  //Getter object1
		&ql::BasicOption<>::Expiry, //Setter object2
		&ql::BasicOption<>::ValueDate); // Getter object2

	EXPECT_EQ(option2->Expiry(), option3->ValueDate());

	EXPECT_EQ(option3->Expiry(), option2->ValueDate());
}