#include <gtest/gtest.h>

#include "DynamicAssert.h"

void throw_or_not_debug(const bool expr, const char * file, int lineno)
{
	using namespace Assert;
	dynamic <LEVEL(Assert::Level::debug_)>(expr, compose(file, lineno, "range problem"));
}

void throw_or_not_release(const bool expr, const char * file, int lineno)
{
	using namespace Assert;
	dynamic <LEVEL(Assert::Level::release_)>(expr, compose(file, lineno, "range problem"));
}

#ifdef _DEBUG
TEST(DynamicAssertUT, CheckCases_DuringDebug) {

	
	const int n = 8;
	
	using namespace Assert;
	ASSERT_EQ(default_level, Level::debug_);
	ASSERT_EQ(current_level, Level::debug_);
	
	// If not specified, checked in debug, but not in release
	EXPECT_THROW({ dynamic((n > 8), compose(__FILE__, __LINE__, "range problem")); },
		Error);
	EXPECT_NO_THROW(dynamic((n == 8), compose(__FILE__, __LINE__, "range problem")));
	
	// If debug_ specified, checked in debug, but not in release
	EXPECT_NO_THROW(throw_or_not_debug((n >= 8), __FILE__, __LINE__));
	EXPECT_THROW(throw_or_not_debug((n > 8), __FILE__, __LINE__), Error);

	// If release_ specified, checked in debug, and  release
	EXPECT_NO_THROW(throw_or_not_release((n >= 8), __FILE__, __LINE__));
	EXPECT_THROW(throw_or_not_release((n > 8), __FILE__, __LINE__), Error); //X

}

#endif

#ifndef _DEBUG
TEST(DynamicAssertUT, CheckCases_DuringRelease) {

	const int n = 8;

	using namespace Assert;
	ASSERT_EQ(default_level, Level::debug_);
	ASSERT_EQ(current_level, Level::release_);

	// If not specified, checked in debug, but not in release
	EXPECT_NO_THROW({ dynamic((n > 8), compose(__FILE__, __LINE__, "range problem")); });
	EXPECT_NO_THROW(dynamic((n == 8), compose(__FILE__, __LINE__, "range problem")));

	// If release_ specified, checked in debug, and  release
	EXPECT_NO_THROW(throw_or_not_release((n >= 8), __FILE__, __LINE__));
	EXPECT_THROW(throw_or_not_release((n > 8), __FILE__, __LINE__), Error);
}
#endif