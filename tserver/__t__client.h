#pragma once

#include <vector>

#include "iComm.h"

#include "SK___t__clientproxy.h"

#include "__t__.pb.h"

class __T__ClientConfig : public Comm::BaseClientConfig
{
public:
	static __T__ClientConfig* GetDefault( const std::string& f );

private:
	__T__ClientConfig( const std::string& f ):BaseClientConfig( f )
	{}
	
	~__T__ClientConfig()
	{}
};


class __T__Client
{
public:
	__T__Client();
	~__T__Client();

	int SetClientConfig( const  std::string & f );

	int GetSectByUin( const unsigned int& iUin );

	int SKGetMetainfo( const unsigned int& iHeadUin,
		std::string& response );

	int SKEcho( const unsigned int& iHeadUin,
		const std::string& request,
		std::string& response );

__T_MOTHOD_P__

	std::string& GetLastErrMsg();
	
private:
	int SetBaseRequest(const unsigned int& iHeadUin, 
		BaseRequest& basereq,
		const std::string& deviceid="", 
		const std::string& deviceType="",
		const std::string& sessionkey="",
		const unsigned int& clientversion=0);
	
private:
	__T__ClientConfig* _poConfig;
	std::string _errmsg;
};
