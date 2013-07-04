#include <iostream>
#include <stdio.h>
#include <RCF/RCF.hpp>

#include "iComm.h"
#include "dn.h"

#include "__t__.pb.h"

#include "SK___t__clientproxy.h"

#include "__t__client.h"

using namespace Comm;

__T__ClientConfig* __T__ClientConfig ::GetDefault( const  std::string & f )
{	
	static __T__ClientConfig config( f );
	return &config;
}


/*****************************************************************/

__T__Client :: __T__Client()
{
	const std::string f = "/home/sspace/etc/client/__t___cli.conf";
	_poConfig = __T__ClientConfig::GetDefault( f );

	int ret = _poConfig->ReloadIfmodified();
	if( ret != COMM_OK )
	{
		LogErr( "ERR: %s(%d) load %s failed, errmsg[%s], ret[%d]", __func__, __LINE__, f.c_str(), _poConfig->GetLastErrMsg().c_str(), ret );
	}
}

__T__Client :: ~__T__Client(){}

int __T__Client :: SetClientConfig( const  std::string & f )
{
	return _poConfig->ResetConfFile( f );
}

int __T__Client :: GetSectByUin( const unsigned int& iUin )
{
	return iUin / ( 100 * 10000 );
}


int __T__Client :: SetBaseRequest(const unsigned int & iHeadUin, 
	BaseRequest& basereq,
	const std :: string & deviceid, 
	const std :: string & deviceType, 
	const std :: string & sessionkey, 
	const unsigned int & clientversion)
{
	basereq.set_uin( iHeadUin );
	basereq.set_deviceid( deviceid );
	basereq.set_devicetype( deviceType );
	basereq.set_clientversion( clientversion );
	basereq.set_sessionkey( sessionkey );
	return 0;
}

int __T__Client :: SKEcho( const unsigned int& iHeadUin,
		const std::string& request,
		std::string& response )
{
	int ret = 0;
	Comm::Endpoint ep;
	ret = _poConfig->GetEndpointBySect( GetSectByUin(iHeadUin), ep);

	if( ret != COMM_OK )
	{
		LogErr("ERR: %s(%d) errmsg[%s], ret[%d]", __func__, __LINE__, _poConfig->GetLastErrMsg().c_str(), ret );
		_errmsg = _poConfig->GetLastErrMsg();
		return -1;
	}

	RCF::RcfInitDeinit rcfInit;
	RcfClient<__T__ServiceDef> rcfClient( RCF::TcpEndpoint(ep.GetIp(), ep.GetPort()) );

	__T__ClientProxy proxyClt;
	ret = proxyClt.SKEcho( rcfClient, iHeadUin, request, response);
	if( ret!=COMM_OK )
	{
		LogErr("ERR: %s(%d) errmsg[%s], ret[%d]", __func__, __LINE__, proxyClt.GetLastErrMsg().c_str(), ret );
		_errmsg = proxyClt.GetLastErrMsg();
		return -1;
	}
	return ret;
}

__T_MOTHOD_P__

std::string& __T__Client :: GetLastErrMsg()
{
	return _errmsg;
}

	
