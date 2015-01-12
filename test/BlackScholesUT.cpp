#include <gtest/gtest.h>
#include "TestBasicOptionFixedValues.h"
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


void BlackScholesOptionUTFixture::SetUp()
{
	option_ = test::TestBasicOptionFixedValues();
};
	


