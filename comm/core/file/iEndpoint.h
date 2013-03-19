#pragma once

#include <vector>
#include <string>

#include "iIniConfig.h"

#include "utils/iString.h"

#include <boost/property_tree/ptree.hpp>

namespace Comm
{
	class Endpoint
	{
	public:
		
		Endpoint( const std::string& sIp, const int iPort,  const int iBeginSect, const int iEndSect )
			:_ip(sIp), _port( iPort ), _beginSect( iBeginSect ), _endSect( iEndSect )
		{
		}

		Endpoint()
			:_ip(""), _port( 0 ), _beginSect( 0 ), _endSect( 0 )
		{
		}
		
		~Endpoint(){}

		std::string*  GetMutableIp(){ return &_ip; }

		int* GetMutablePort(){ return &_port; }

		int* GetMutableBeginSect(){ return &_beginSect; }

		int* GetMutableEndSect(){ return &_endSect; }

		const char* GetIp() { return _ip.c_str(); }

		const int GetPort() { return _port; }

		const int GetBeginSect(){  return _beginSect; }

		const int GetEndSect(){ return _endSect; }

		bool IsInSect( int sect)
		{
			return ( _beginSect <= sect && sect <= _endSect ) ;
		}

		void Reset()
		{
			_ip = "";
			_port = _beginSect = _endSect =0;
		}
		
	private:
		std::string _ip;
		int _port;
		int _beginSect;
		int _endSect;
	};
	
	class EndpointMgr
	{
	public:
		EndpointMgr( std::string sectionPrefix );
		~EndpointMgr();

		int Init( IniConfig* iniConfig );

		int GetEndpointBySect( const int sect , Endpoint& endpoint);

		int GetEndpointSize();

		std::string& GetLastErrMsg();
		
	private:
		std::string _sectionPrefix;
		IniConfig* _iniConfig;
		std::vector<Endpoint> _VecEndpoint;
		std::string _errmsg;
	};
		
}
