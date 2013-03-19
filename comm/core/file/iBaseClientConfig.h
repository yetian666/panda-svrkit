#pragma once

#include <string>

#include "iEndpoint.h"
#include "iIniConfig.h"

namespace Comm
{
	class BaseClientConfig : public IniConfig
	{
	public:
		BaseClientConfig( const std::string& sConfig );
		~BaseClientConfig();

		int Init();

		int GetEndpointBySect( const int iSect, Endpoint& poEndpoint );

	protected:
		virtual int Read();
		
	private:
		int _iConnRetryCount;
		int _iConnTimeout;
		int _iIOTimeout;
		
		EndpointMgr* _poEndpointMgr;
	};
}
