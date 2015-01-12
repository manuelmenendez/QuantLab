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

} //namespace Assert



