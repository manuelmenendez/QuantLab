#include <gtest/gtest.h>
#include "BasicOption.h"

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
