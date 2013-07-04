#include <stdio.h>
#include <vector>

#include "__t__testimpl.h"
#include "__t__client.h"

#include "iComm.h"

using namespace std;

int __T__TestImpl :: SKEcho( Comm::OptionMap& optMap )
{
	unsigned int iUin = 0;
	if( optMap.GetValue( 'u', &iUin)!=COMM_OK )
	{
		printf("ERR: cant get uin\n");
		return -1;
	}
	
	__T__Client client;
	std::string res;

	int ret = client.SKEcho(iUin, "SkEcho_test", res);
	if(  ret!=COMM_OK)
	{
		printf("ERR: ret %d errmsg %s\n", ret, client.GetLastErrMsg().c_str() );
		return ret;
	}

	printf("ret %d errmsg %s echo res %s\n", ret, client.GetLastErrMsg().c_str() , res.c_str() );
	return 0;
}

__T_MOTHOD_P__

