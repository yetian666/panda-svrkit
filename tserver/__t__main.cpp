#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

#include <RCF/RCF.hpp>

#include "iComm.h"

#include "__t__.pb.h"
#include "__t__serviceimpl.h"

using namespace std;
using namespace Comm;

RCF::RcfServer *g_poRcfServer = NULL;

int main(int argc, char**argv)
{
	OpenLogfile( "__t__", "/home/sspace/log/error" );

	char sConfig[256] = {0};
	int iDaemon = 0;

	if( Comm::CommandLine( argc, argv, "__t__", &iDaemon, sConfig, sizeof(sConfig))!=0 )
	{
		LogErr("CommandLine parse failed");
		exit(1);
	}

	if( iDaemon  )
	{
		Comm::ForkAsDaemon();
	}
	
	//while( 1 )
	{
		RCF::RcfInitDeinit rcfInit;

		__T__ServiceImpl serviceImpl;
	
		__T__Service *service = &serviceImpl;
	
		if( g_poRcfServer == NULL )
		{
			g_poRcfServer = new RCF::RcfServer( RCF::TcpEndpoint("127.0.0.1", 10001) );
		}

		g_poRcfServer->bind<__T__ServiceDef>(*service);

		RCF::ThreadPoolPtr tpPtr( new RCF::ThreadPool(8) );

		g_poRcfServer->setThreadPool(tpPtr);
		g_poRcfServer->start();
		
		g_poRcfServer->waitForStopEvent();

		LogErr("Server main thread stoped, restart later");

		delete g_poRcfServer;
		g_poRcfServer = NULL;
	}

	return 0;
}
