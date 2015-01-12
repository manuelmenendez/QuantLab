#include "DynamicAssert.h"

namespace Assert{

	// Compose message including file name a and line number
	inline	
	std::string compose(const char * file, int line, const std::string & message)
	{
		std::ostringstream os("");
		os << file << "," << line << "):" << message;
		return os.str();
	}

	//template <const bool  condition, class Except > inline
	//void dynamic(const bool assertion, const std::string & message = "Assert::dynamic failed")
	//{
	//	if (assertion)
	//		return;
	//	if (current_mode == Mode::throw_)
	//		throw Except(message);
	//	if (current_mode == Mode::terminate_)
	//		std::terminate();
	//}

	//template <>
	//void dynamic<false, Assert::Error>(bool, const std::string &);

	template <> inline 
	void dynamic<false, Assert::Error>(bool, const std::string &){}

		
	inline 
	void dynamic(const bool b, const std::string & s)
	{
		dynamic< LEVEL(0), Assert::Error>(b, s);
	}

	inline 
	void dynamic(const bool b)
	{
		dynamic< LEVEL(0), Assert::Error>(b, "Assert::dynamic failed");
	}
	
	//template <> inline
	//void dynamicL<Assert::Level::debug_, Assert::Error>(const bool b, const std::string & s){
	//	if (static_cast<int>(Assert::Level::debug_) >= static_cast<int>(Assert::current_level))
	//		dynamic(b, s);
	//}


	//template <> inline
	//	void dynamicL<Assert::Level::release_, Assert::Error>(const bool b, const std::string & s){
	//		if (static_cast<int>(Assert::Level::release_) >= static_cast<int>(Assert::current_level))
	//			dynamic(b, s);
	//	}


} //namespace Assert



