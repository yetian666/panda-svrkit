#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <assert.h>

#include "iRunTime.h"
#include "iStressTest.h"

using namespace std;

namespace Comm
{
	typedef struct tagStressTestStat
	{
		int reqCountProcessed;
		int reqCountLastTimeProcessed;
		int maxTimeCost;
	}StressTestStat_t;
	
	void StressSignalTestStop( int sig )
	{
		int pid, stat;
		pid = (int)waitpid(0, &stat, WNOHANG);
		printf("%u exited, kill all\n", pid);
		::kill( 0, SIGKILL);
	}

	int StressTestInit(StressTestStat_t** pShm, int maxProcessSize )
	{
		string sLockFile="/tmp/stresstest.lock";
		
		int iFd = open( sLockFile.c_str(), O_RDWR | O_NONBLOCK | O_CREAT, 0666 );

		if( iFd < 0 ) 
		{
			printf("ERR:%s(%d) open lock file %s err:%s\n", __func__,__LINE__,sLockFile.c_str(),strerror(errno));
			return -1;
		}

		key_t tShmKey = ftok( sLockFile.c_str(), 0 );

		if( tShmKey < 0 )
		{
			printf("ERR:%s(%d) ftok file:%s key:%d err:%s\n", __func__,__LINE__,sLockFile.c_str(), tShmKey,strerror(errno));
			return -1;
		}

		int iMode = 0640;

		int iShmId;
		
		if ((iShmId = shmget(tShmKey, maxProcessSize*sizeof(StressTestStat_t), IPC_CREAT | IPC_EXCL | iMode)) < 0)	//try to create
		{
			if (errno != EEXIST)
			{
				printf("%s(%d) shmget %s\n" , __FILE__, __LINE__, strerror(errno));
				return -1;
			}	

			if ((iShmId = shmget(tShmKey, maxProcessSize*sizeof(StressTestStat_t), iMode)) < 0)
			{
				printf("%s(%d) shmget %s\n" , __FILE__, __LINE__, strerror(errno));
				return -1;
			}
		}

		if (( (*pShm) = (StressTestStat_t*)shmat(iShmId, NULL, 0)) < 0)
		{
			printf("%s(%d) shmat %s\n" , __FILE__, __LINE__, strerror(errno));
			return -1;
		}

		assert ( sigset ( SIGCHLD, StressSignalTestStop ) != SIG_ERR ) ;
		
		return 0;
	}

	int StressTestRun( int forkCount, StressTestRPCCall stressTestRpcCall, int timeout )
	{	
		StressTestStat_t *pStressTestStats = NULL;
		
		if( StressTestInit(&pStressTestStats, 512)!=0)
		{
			printf("Init shm err\n");
			exit(1);
		}
		
		printf("fork count %d\n", forkCount);
		
		memset((char*)pStressTestStats, 0, sizeof(StressTestStat_t)*forkCount);
		
		for(int i=0; i<forkCount; i++)
		{
			pid_t pid = fork();
			if( pid ==0 )
			{
				RunTime t;
				while( 1 )
				{	
					int ret = stressTestRpcCall();

					int runTimeCost = t.GetFuncRunTime();

					pStressTestStats[i].maxTimeCost = max(runTimeCost, pStressTestStats[i].maxTimeCost);
					
					pStressTestStats[i].reqCountProcessed++; 
					
					if( runTimeCost > timeout || ret != 0) 
					{
						if(runTimeCost > timeout)
							printf("runTimeCost %d > %ds, exit\n", runTimeCost, timeout/1000);
						if( ret != 0)
							printf("req ret %d, exit\n", ret);
						
						pStressTestStats[i].reqCountProcessed=-1;
						exit(0);
					}
				}
			}

			printf("process %d,%d started\n", i, (int)pid);
		}

		printf("fork  %d process over\n", forkCount);

		StressTestStat_t finalStat;
		memset((char*)&finalStat, 0, sizeof(StressTestStat_t));
		
		while( 1 )
		{
			unsigned int tnow = (unsigned int)time(NULL);
			sleep(1);
			finalStat.reqCountLastTimeProcessed = finalStat.reqCountProcessed;
			finalStat.reqCountProcessed = 0;
			for(int i = 0; i<forkCount; i++)
			{
				finalStat.reqCountProcessed+=pStressTestStats[i].reqCountProcessed;
				finalStat.maxTimeCost = max(pStressTestStats[i].maxTimeCost, finalStat.maxTimeCost);
			}

			printf("%u -----> %u, over reqCout %u, maxTimeCost %d\n", tnow, (unsigned int)time(NULL), 
				finalStat.reqCountProcessed-finalStat.reqCountLastTimeProcessed,
				finalStat.maxTimeCost );
		}
		return 0;

	}
}

/*
	让TIME_WAIT状态可以重用，这样即使TIME_WAIT占满了所有端口，也不会拒绝新的请求造成障碍
	echo "1" > /proc/sys/net/ipv4/tcp_tw_reuse
	让TIME_WAIT尽快回收，我也不知是多久，观察大概是一秒钟
	echo "1" > /proc/sys/net/ipv4/tcp_tw_recycle
*/


