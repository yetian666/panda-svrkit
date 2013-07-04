#include "SK___t__clientproxy.h"

using namespace std;

using Comm::Endpoint;


int __T__ClientProxy :: SKGetMetainfo( __T__RcfClinet& rcfClient, 
	const unsigned int& iHeadUin,
	std::string& response )
{
	return rcfClient.SKGetMetainfo( response);
}

int __T__ClientProxy :: SKEcho( __T__RcfClinet& rcfClient, 
	const unsigned int& iHeadUin,
	const std::string& request,
	std::string& response )
{
	return rcfClient.SKEcho( request, response);
}

__T_MOTHOD_P__

std::string& __T__ClientProxy :: GetLastErrMsg()
{
	return _errmsg;
}