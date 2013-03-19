#include <string.h>
#include "iComm.h"
#include "iBaseClientConfig.h"

namespace Comm
{
	BaseClientConfig :: BaseClientConfig( const std::string& sConfig) : 
		IniConfig( sConfig )
	{
		_poEndpointMgr = new EndpointMgr( "Server" );
	}

	BaseClientConfig :: ~BaseClientConfig()
	{
		if( _poEndpointMgr )
			delete _poEndpointMgr;
	}

	int BaseClientConfig :: Init()
	{
		return Read();
	}

	int BaseClientConfig :: Read()
	{
		//IniConfig :: Read();
		
		//init ini config
		int ret = IniConfig :: Init();

		if( ret != COMM_OK )
		{
			return ret;
		}

		//init endpoints
		ret = _poEndpointMgr->Init( this );

		if( ret != COMM_OK )
		{
			_errmsg = _poEndpointMgr->GetLastErrMsg();
			return ret;
		}

		//init client conn args
		const char* ClientConnSection = "ClientTimeout";
		
		ConfigItemInfo_t configItemArray[] = 
		{
			CONFIG_ITEM_INT(ClientConnSection, "ConnRetryCount", _iConnRetryCount ),
			CONFIG_ITEM_INT(ClientConnSection, "ConnTimeoutMS", _iConnTimeout ),
			CONFIG_ITEM_INT(ClientConnSection, "SockTimeout", _iIOTimeout),
			CONFIG_ITEM_END
		};

		ret = DumpConfig( configItemArray );
		
		return ret;
	}

	int BaseClientConfig :: GetEndpointBySect(const int iSect, Endpoint& poEndpoint)
	{
		int ret = _poEndpointMgr->GetEndpointBySect( iSect, poEndpoint );

		if( ret != COMM_OK )
		{
			_errmsg = _poEndpointMgr->GetLastErrMsg();
		}

		return ret;
	}
}
