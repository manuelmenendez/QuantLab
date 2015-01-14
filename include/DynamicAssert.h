// Dynamic assertions. Seee "Bjarne Stroustrup, The C++ Programming Language", 13.4
// Other alternative could be boost assertions
// Adapted to MSVC 2013
// Rewrite when VS supports constexpr

#ifndef DASSERT_H
#define DASSERT_H

#if ( _MSC_VER <= 1800 )
#define constexpr_ const
#else
#define constexpr_ constexpr
#endif

#ifndef ASSERT_CURRENT_MODE 
#define ASSERT_CURRENT_MODE Assert::Mode::throw_
#endif

#ifndef ASSERT_CURRENT_LEVEL
#ifdef _DEBUG
#define ASSERT_CURRENT_LEVEL Assert::Level::debug_
#endif
#ifndef _DEBUG
#define ASSERT_CURRENT_LEVEL Assert::Level::release_
#endif
#endif

#define LEVEL(X)  (static_cast<int>(X) >= static_cast<int>(Assert::current_level))

#include <stdexcept>
#include <string>
#include <sstream>

namespace Assert
{

// If not specified, assertions are evaluated only in debug
// If level of assertion is debug_, is evaluated in debug, but not in release
// If level of assertion is release_,  is evaluated both in debug and release 

	enum  class Mode { ignore_, throw_, terminate_ };
	enum  class Level{ debug_ = 0, release_= 1 };

	constexpr_ Mode current_mode = ASSERT_CURRENT_MODE;
	constexpr_ Level current_level = ASSERT_CURRENT_LEVEL;
	constexpr_ Level default_level = Level::debug_; 

	struct Error : std::runtime_error
	{
		Error(const std::string & p) :std::runtime_error(p){}
	};

	// Compose message including file name a and line number

	std::string compose(const char * file, int line, const std::string & message);

	void dynamic(bool b, const std::string & s);

	void dynamic(bool b);

	template <const bool  condition = LEVEL(ASSERT_CURRENT_LEVEL), class Except = Error>
	void dynamic(const bool assertion, const std::string & message)
	{
			if (assertion)
				return;
			if (current_mode == Mode::throw_)
				throw Except(message);
			if (current_mode == Mode::terminate_)
				std::terminate();
	}

	void dynamic_release(bool expr, const char* file, const int lineno, const std::string & message);
} //namespace Assert

#include "DynamicAssert.inl"

#endif DASSERT_H