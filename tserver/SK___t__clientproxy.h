#pragma once

#include <string>

#include "iComm.h"

#include "dn.h"

#include "__t__.pb.h"

#include "SK___t__servicedef.h"

using Comm::Endpoint;

//__T__RcfClinet will change in rpc call , so cannot use const
typedef RcfClient<__T__ServiceDef> __T__RcfClinet;

class __T__ClientProxy
{	
public:

	int SKGetMetainfo( __T__RcfClinet& rcfClient, 
		const unsigned int& iHeadUin,
		std::string& response );

	int SKEcho( __T__RcfClinet& rcfClient, 
		const unsigned int& iHeadUin,
		const std::string& request,
		std::string& response );
	
__T_MOTHOD_P__

	std::string& GetLastErrMsg();
private:
	std::string _errmsg;
};
