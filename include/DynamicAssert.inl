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

	template <const bool  condition, class Except > inline
	void dynamic(const bool assertion, const std::string & message = "Assert::dynamic failed")
	{
		if (assertion)
			return;
		if (current_mode == Mode::throw_)
			throw Except(message);
		if (current_mode == Mode::terminate_)
			std::terminate();
	}

	template <> inline 
	void dynamic<false, Error>(bool, const std::string &){}

		
	inline 
	void dynamic(bool b, const std::string & s)
	{
		dynamic<true, Error>(b, s);
	}

		
	inline 
	void dynamic(bool b)
	{
		dynamic<true, Error>(b);
	}
	

} //namespace Assert



