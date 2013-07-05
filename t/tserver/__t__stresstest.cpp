#include <iostream>
#include <stdio.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <RCF/RCF.hpp>

#include "SK___t__servicedef.h"
#include "SK___t__clientproxy.h"
#include "iComm.h"

#include "dn.h"
#include "__t__client.h"

using namespace std;

using namespace Comm;


int RpcCallRcf()
{
	__T__Client client;
	string sResp;
	
	int ret = client.SKEcho( 10001, "stresstest", sResp);
	if(  ret !=COMM_OK)
	{
		LogDebug("ERR: ret %d errmsg %s", ret, client.GetLastErrMsg().c_str() );
		return ret;
	}

	return 0;
}

int main( int argc, char* argv[] )
{
	OpenLogfile("__t__stresstest", "/home/sspace/log/error" );
	if( argc < 3 )
	{
		printf("usage: %s processCount timeout\n", argv[0]);
		return -1;
	}
	printf("stresstest Rcf\n");
	return Comm::StressTestRun( atoi(argv[1]), RpcCallRcf, atoi(argv[2]));
}

/*
	让TIME_WAIT状态可以重用，这样即使TIME_WAIT占满了所有端口，也不会拒绝新的请求造成障碍
	echo "1" > /proc/sys/net/ipv4/tcp_tw_reuse
	让TIME_WAIT尽快回收，我也不知是多久，观察大概是一秒钟
	echo "1" > /proc/sys/net/ipv4/tcp_tw_recycle
*/
