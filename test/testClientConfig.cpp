#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

#include "iComm.h"

using namespace std;



int ClientConfigInitTest( const string& f )
{
	Comm ::BaseClientConfig clientConfig( f );

	int ret = clientConfig.Init();
	printf("%s msg:"TnClRED"%s"TnClEND", ret:%d\n", __func__, clientConfig.GetLastErrMsg().c_str(), ret );
	
	string sAddr;
	ret = clientConfig.GetValue("Server0", "SVR_IP", sAddr);
	printf("%s clientConfig.GetValue Server0 sAddr %s, msg "TnClRED"%s"TnClEND", ret:%d\n", __func__, sAddr.c_str(), clientConfig.GetLastErrMsg().c_str(), ret );
	
	ret = clientConfig.GetValue("Server0", "SVR_IP_noexist", sAddr);
	printf("%s clientConfig.GetValue SVR_IP_noexist msg "TnClRED"%s"TnClEND", ret:%d\n", __func__, clientConfig.GetLastErrMsg().c_str(), ret );

	return ret;
}


int ClientConfigDumpTest( const string& f , const string& section )
{
	Comm ::BaseClientConfig clientConfig( f );

	int ret = clientConfig.Init();
	
	Comm::Endpoint endpoint;
	
	Comm::ConfigItemInfo_t configItemArray[] = 
	{
		CONFIG_ITEM_STR( section.c_str(), "SVR_IP", *(endpoint.GetMutableIp()) ),
		CONFIG_ITEM_INT(section.c_str(), "SVR_Port", *(endpoint.GetMutablePort()) ),
		CONFIG_ITEM_INT(section.c_str(), "Sect_Begin", *(endpoint.GetMutableBeginSect()) ),
		CONFIG_ITEM_INT(section.c_str(), "Sect_End", *(endpoint.GetMutableEndSect()) ),
		CONFIG_ITEM_END
	};

	ret = clientConfig.DumpConfig( configItemArray );
	printf("%s %s ip %s, port %d, [%d,%d] ERR: msg "TnClRED"%s"TnClEND", ret %d\n", 
		__func__, section.c_str(), endpoint.GetIp(), endpoint.GetPort(), endpoint.GetBeginSect(), endpoint.GetEndSect(),clientConfig.GetLastErrMsg().c_str(), ret );

	return ret;
}


int ClientConfigGetEnpointTest( const string& f, const int& sect )
{
	Comm ::BaseClientConfig clientConfig( f );

	int ret = clientConfig.Init();
	
	Comm::Endpoint endpoint;
	ret = clientConfig.GetEndPointBySect(sect, endpoint);
	if( ret==0 )
	{
		printf("%s %d  ip %s, port %d, [%d,%d] ERR: msg "TnClRED"%s"TnClEND", ret %d\n", 
			 __func__, sect,endpoint.GetIp(), endpoint.GetPort(), endpoint.GetBeginSect(), endpoint.GetEndSect(),clientConfig.GetLastErrMsg().c_str(), ret );
	}
	else
	{
		printf("%s %d msg "TnClRED"%s"TnClEND", ret:%d\n", __func__, sect, clientConfig.GetLastErrMsg().c_str(), ret );
	}
	return ret;
}

int main( int argc, char* argv[] )
{
	if( argc < 2)
	{
		printf("%s file <configure file>\n", argv[0] );
		return -1;
	}

	string configFile = argv[1];

	ClientConfigInitTest( configFile );

	ClientConfigDumpTest( configFile , "Server0" );

	ClientConfigDumpTest( configFile , "Server10010" );

	ClientConfigGetEnpointTest( configFile, 0 );

	ClientConfigGetEnpointTest( configFile, 10000 );
	
	return 0;
}
