#include <gtest/gtest.h>
#include "BasicOption.h"
#include "BasicOptionUT.h"
#include "TestBasicOptionFixedValues.h"



void BasicOptionOptionUTFixture::SetUp()
{
	option_ = test::TestBasicOptionFixedValues();
};


TEST(BasicOptionUT, DefaultConstructor) {

	using namespace ql;
	BasicOption<> myOption;
	EXPECT_EQ(ql::PutCallT::Unassigned, myOption.PutCall());
	EXPECT_EQ(0.0, myOption.Dividends());
}

TEST(BasicOptionUT, Preconditions) {

	using namespace ql;
	BasicOption<> myOption;
	EXPECT_EQ(ql::PutCallT::Unassigned, myOption.PutCall());
	EXPECT_EQ(0.0, myOption.Dividends());
}

TEST(BasicOptionUT, leessThnazero) {

	using namespace ql;
	BasicOption<> myOption;
	EXPECT_EQ(ql::PutCallT::Unassigned, myOption.PutCall());
	EXPECT_EQ(0.0, myOption.Dividends());
}
