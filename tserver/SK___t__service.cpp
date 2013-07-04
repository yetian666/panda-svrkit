#include "SK___t__service.h"

#include "dn.h"
#include "iComm.h"
using namespace Comm;

int __T__Service :: SKGetMetainfo(std::string& tResponse )
{
	return 0;
}

int __T__Service :: SKEcho( const std::string& request,
	std::string& response )
{
	response = request;
	
	LogDebug("%s(%d) %s", __func__, __LINE__, request.c_str() );

	return 0;
}

__T_INNER_MOTHOD_P__

std::string __T__Service :: GetErrMsg()
{
	return _errmsg;
}


/**************below func you must impelement in class __T__ServiceImpl****************/

__T_OUTER_MOTHOD_P__
