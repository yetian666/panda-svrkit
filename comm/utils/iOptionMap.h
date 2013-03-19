#pragma once

#include <map>
#include <sstream>

namespace Comm
{
	class OptionMap
	{
		public:
			OptionMap( const char* optStr );
			virtual ~OptionMap();

			int Parse( const int argc, char* argv[] );

			template <typename Type>
			int GetValue( const char& c, Type* v )
			{
				const OptionStrMap::const_iterator it = _optionStrMap.find( c );
				
				if( it != _optionStrMap.end() )
				{
					std::stringstream sstr;
					sstr << it->second;
					sstr >> (*v);
					return 0;
				}

				return -1;
			}

		private:
			typedef std::map< char, std::string> OptionStrMap;

			OptionStrMap _optionStrMap;

			const char* _optStr;
	};
}

