// Dynamic assertions. Seee "Bjarne Stroustrup, The C++ Programming Language", 13.4
// Other alternative could be boost assertions
// Adapted to MSVC 2013

#ifndef DASSERT_H
#define DASSERT_H

#if ( _MSC_VER <= 1800 )
#define constexpr_ const
#else
#define constexpr_ constexpr
#endif

#ifndef CURRENT_MODE
#define CURRENT_MODE Assert::Mode::terminate_
#endif

#ifndef CURRENT_LEVEL
#define CURRENT_LEVEL 1
#endif


#include <stdexcept>
#include <string>
#include <sstream>

namespace Assert
{

	enum  class Mode{ throw_, terminate_, ignore_ };

	constexpr_ int current_level = CURRENT_LEVEL;
	constexpr_ int default_level = 1;
	constexpr_ Mode current_mode = CURRENT_MODE;

	constexpr_ bool level(int n);


	struct Error : std::runtime_error
	{
		Error(const std::string & p) :std::runtime_error(p){}
	};

	// Compose message including file name a and line number

	std::string compose(const char * file, int line, const std::string & message);

	void dynamic(bool b, const std::string & s);

	void dynamic(bool b);

	template <const bool  condition = level(default_level), class Except = Error>
	void dynamic(const bool assertion, const std::string & message);

	template <>
	void dynamic<false, Error>(bool, const std::string &);


} //namespace Assert

#include "DynamicAssert.inl"

#endif DASSERT_H