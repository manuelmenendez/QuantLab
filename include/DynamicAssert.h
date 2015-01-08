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

#ifndef ASSERT_CURRENT_MODE 
#define ASSERT_CURRENT_MODE Mode::throw_
#endif

#ifndef ASSERT_CURRENT_LEVEL
#ifdef _DEBUG
#define ASSERT_CURRENT_LEVEL Level::debug_
#endif
#ifndef _DEBUG
#define ASSERT_CURRENT_LEVEL Level::release_
#endif
#endif


#include <stdexcept>
#include <string>
#include <sstream>

namespace Assert
{
//Si no pongo nada, se comprueba en debug, pero no en release,
//Si pongo debug, se comprueba en debug pero no en release
//Si pongo release, se comprueba en debug y en release

#pragma message("revisar niveles")
	enum  class Mode { ignore_, throw_, terminate_ };
	enum  class Level{ debug_ = 0, release_=1};

	constexpr_ Mode current_mode = ASSERT_CURRENT_MODE;
	constexpr_ Level current_level = ASSERT_CURRENT_LEVEL;
	constexpr_ Level default_level = Level::release_;

	inline constexpr_ bool level(int n) {
			return static_cast<int>(n) <= static_cast<int>(current_level);
	}

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