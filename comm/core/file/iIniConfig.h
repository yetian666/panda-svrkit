#pragma once
#include <time.h>

#include <boost/property_tree/ptree.hpp>

/*
TODO: need support default value like CONFIG_ITEM_STR( "Datafile", "Path",  m_sDataFilePath),
*/
#define CONFIG_ITEM_TYPE_NON 0
#define CONFIG_ITEM_TYPE_INT 1
#define CONFIG_ITEM_TYPE_STR 2


#define CONFIG_ITEM_STR(section, key, var) \
	{ section, key, CONFIG_ITEM_TYPE_STR, (void*)&(var)}

#define CONFIG_ITEM_INT(section, key, var) \
	{ section, key, CONFIG_ITEM_TYPE_INT, (void*)&(var) }

#define CONFIG_ITEM_END \
	{ "", "", CONFIG_ITEM_TYPE_NON, NULL }

namespace Comm
{
	typedef struct tagConfigItemInfo 
	{
		const char * sSection;
		const char * sKey;
		int  iType;
		void * pvAddr;
	} ConfigItemInfo_t;
	
	class IniConfig
	{

	public:
		IniConfig( const std::string& filePath );
		~IniConfig();

		int Init();
		
		int ReloadIfmodified();

		std::string& GetIniPath();

		template< typename Type>
		int GetValue( const std::string& section, const std::string& name, Type& v )
		{
			try
			{
				v = _iniPt.get<Type>(section+"."+name);
			}
			catch( boost::property_tree::ptree_error& e )
			{
				_errmsg = e.what();
				return -1;
			}

			return 0;
		}

		int DumpConfig( ConfigItemInfo_t* configItemInfoArray  );

		std::string& GetLastErrMsg();

	protected:
		virtual int Read();

		int  GetLastWriteTime( std::time_t& t );
		
	private:
		std::string _iniFilePath;
		std::time_t _lastWriteTime;

		boost::property_tree::ptree _iniPt;

	protected:
		std::string _errmsg;
	};
}
