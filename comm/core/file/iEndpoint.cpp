#include "iEndpoint.h"

namespace Comm
{

	EndpointMgr :: EndpointMgr( std::string sectionPrefix):
		_sectionPrefix( sectionPrefix )
	{
	}

	EndpointMgr :: ~EndpointMgr()
	{}
	
	int EndpointMgr :: Init( IniConfig* iniConfig )
	{
		int ret = 0;
		
		_iniConfig = iniConfig;
		
		int serverCount = 0;
		if( (ret = _iniConfig->GetValue( _sectionPrefix, "ServerCount", serverCount ) ) !=0 )
		{
			_errmsg = __func__+ std::string(" Get server count fail, ") + _iniConfig->GetLastErrMsg();
			return ret;
		}

		Endpoint endpoint;
		
		for( int i = 0; i<serverCount; i++ )
		{
			std::string section = StrCat( _sectionPrefix, i );
			
			ConfigItemInfo_t configItemArray[] =
			{
				CONFIG_ITEM_STR( section.c_str(), "SVR_IP", *(endpoint.GetMutableIp()) ),
				CONFIG_ITEM_INT(section.c_str(), "SVR_Port", *(endpoint.GetMutablePort()) ),
				CONFIG_ITEM_INT(section.c_str(), "Sect_Begin", *(endpoint.GetMutableBeginSect()) ),
				CONFIG_ITEM_INT(section.c_str(), "Sect_End", *(endpoint.GetMutableEndSect()) ),
				CONFIG_ITEM_END
			};

			if( (ret = _iniConfig->DumpConfig( configItemArray ) ) !=0 )
			{
				_errmsg = __func__+ std::string(" DumpConfig fail") +iniConfig->GetLastErrMsg();
				return ret;
			}

			_VecEndpoint.push_back( endpoint );
		}

		return ret;
	}
	
	int EndpointMgr :: GetEndpointBySect( const int sect , Endpoint& endpoint)
	{
		endpoint.Reset();
		
		std::vector<Endpoint>::iterator it = _VecEndpoint.begin();
		for( ; it!=_VecEndpoint.end(); it++ )
		{
			if( it->IsInSect(sect) )
			{
				endpoint=*it;
				return 0;
			}
		}

		_errmsg = StrCat( "EndpointMgr cant find endpoint by sect ", sect);
		return -1;
	}

	int EndpointMgr :: GetEndpointSize()
	{
		return _VecEndpoint.size();
	}

	std::string& EndpointMgr :: GetLastErrMsg()
	{
		return _errmsg;
	}
}