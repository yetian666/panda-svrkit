#include <unistd.h>
#include <stdio.h>
#include "iOptionMap.h"

namespace Comm
{
	OptionMap::OptionMap(const char * optStr)
		:_optStr( optStr )
	{}

	OptionMap::~OptionMap()
	{}

	int OptionMap :: Parse(const int argc, char * argv [ ])
	{
		int ret = 0;
		char c ;
		while( ( c = getopt ( argc, argv, _optStr) ) != EOF )
		{
			if( '?' == c || ':' == c )
			{
				ret = -1;
			} else {
				_optionStrMap[c] = ( NULL == optarg ) ? "" : optarg;
			}
		}
		return 0;	
	}
	
}
