#include <gtest/gtest.h>
#include "DynamicAssert.h"


TEST(DynamicAssertUT, DefaultConstructor) {

	int n = 8;

	Assert::dynamic( (n>8), Assert::compose(__FILE__,__LINE__,"range problem"));

}

