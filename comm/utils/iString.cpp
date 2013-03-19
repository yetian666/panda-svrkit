#include <string>
#include <stdio.h>

#include "iString.h"

using std::string;

namespace Comm
{
	string IntToStr(const int i)
	{
		char szStr[16];
		sprintf(szStr,"%d",i);
		return string(szStr);
	}

	string UIntToStr(const unsigned int i)
	{
		char szStr[16];
		sprintf(szStr,"%u",i);
		return string(szStr);
	}

	string LLIntToStr(const long long int i)
	{
		char szStr[32];
		sprintf(szStr, "%lld", i);
		return string(szStr);
	}
		
}
