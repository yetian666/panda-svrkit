
#include "iIniConfig.h"
#include "iComm.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::property_tree;
using namespace boost::filesystem;

using  boost::system::error_code;


namespace Comm
{
	IniConfig :: IniConfig( const std::string& filePath )
	{
		_iniFilePath = filePath;
	}

	IniConfig :: ~IniConfig(){}

	int IniConfig :: Init()
	{
		return IniConfig :: Read();
	}

	int IniConfig :: GetLastWriteTime( std::time_t& t )
	{
		try
		{
			boost::filesystem::path p( _iniFilePath );
			t = last_write_time( p );	
		}
		catch( boost::system::system_error& e)
		{
			_errmsg = e.what();
			return -1;
		}

		return 0;
	}
	
	int IniConfig :: Read()
	{
		static boost::mutex mx;
		boost::mutex::scoped_lock scopedLock(mx);
		
		try 
		{
			ini_parser::read_ini( _iniFilePath, _iniPt );
		}
		catch( ini_parser::ini_parser_error &e)
		{
			_errmsg = e.message();
			return -1;
		}

		GetLastWriteTime( _lastWriteTime );
		
		return 0;
	}


	int IniConfig :: ReloadIfmodified()
	{
		std::time_t lastWriteTime = 0;

		if( 0!= GetLastWriteTime( lastWriteTime ) )
		{
			_errmsg.append(",ReloadIfmodified->GetLastWriteTime fail");
			return -1;
		}

		if( lastWriteTime!=_lastWriteTime )
		{
			return Read();
		}
		
		return 0;
	}

	std::string& IniConfig :: GetIniPath()
	{
		return _iniFilePath;
	}

	int IniConfig :: DumpConfig( ConfigItemInfo_t* configItemInfoArray )
	{
		int ret =0;
		
		for( int i =0;configItemInfoArray[i].pvAddr!=NULL;i++)
		{
			switch( configItemInfoArray[i].iType )
			{
				case CONFIG_ITEM_TYPE_INT:
					ret = GetValue(configItemInfoArray[i].sSection, configItemInfoArray[i].sKey, *(int*)configItemInfoArray[i].pvAddr );
					break;
				case CONFIG_ITEM_TYPE_STR:
					ret = GetValue(configItemInfoArray[i].sSection, configItemInfoArray[i].sKey, *(std::string*)configItemInfoArray[i].pvAddr );
					break;
				default:
					_errmsg = StrCat("DumpConfig there is some type not int or string, type ",configItemInfoArray[i].iType);
					ret--;
			}
				
		}

		return ret;
	}

	std::string& IniConfig :: GetLastErrMsg()
	{
		return _errmsg;
	}
	
}
