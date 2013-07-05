#pragma once
#include <string>

#include "SK___t__servicedef.h"
#include "__t__.pb.h"

class __T__Service
{	
public:
	__T__Service(){}

	virtual ~__T__Service(){}
	
	virtual int SKGetMetainfo(std::string& tResponse );

	virtual int SKEcho( const std::string& request,
		std::string& response );

public:
__T_OUTER_MOTHOD_P__

	std::string GetErrMsg();
	
public:
__T_INNER_MOTHOD_P__

protected:
	std::string _errmsg;
};
