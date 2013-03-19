#pragma once

#include <string>
#include <sstream>

namespace Comm
{
	std::string IntToStr(const int i);

	std::string UIntToStr(const unsigned int i);

	std::string LLIntToStr(const long long int i);

	template <typename Type>
	std::string StrCat( const std::string& s1, Type v)
	{
		std::string ret = s1;
		
		std::stringstream oss;
		oss<<v;
		return ret.append( oss.str() );
	}
}
