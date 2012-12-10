#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <pthread.h>

#include "iLogShmQueue.h"
#include "iShm.h"
#include "iMagicNum.h"
#include "iException.h"

using namespace unistdext;
using namespace stdext;

namespace Comm
{
	LogShmQueue :: LogShmQueue():_shm(NULL)
	{
	}

	LogShmQueue :: ~LogShmQueue()
	{}

	LogShmQueue ::WriteOwnLog(const char * sFmt,...)
	{
		va_list ap;
		va_start( ap, sFmt );
		
		int mode = 0666;

		int fd = open("/home/panda/log/error/logshmqueue", O_RDWR|O_APPEND|O_CREAT, mode);
		if( fd >= 0 )
		{
			struct stat st;
			if( fstat( fd, &st) == 0 && st.st_size >=1600*1024*1024)
			{
				ftruncate( fd, 0 );
			}

			char buf[2048];

			snprintf( buf, sizeof(buf), "<%ld,%ld> ", getpid(), pthread_self() );
			
			time_t now = time( NULL );
			struct tmpTm;
			
			struct *tm tmNow = localtime_r( now, &tmpTm);

			char tStr[64];
			strftime( tStr, 64, "%x %X", tmNow);

			int len = strlen(buf);
			snprintf( buf+len, sizeof(buf)-len, "%s " , tStr);

			len = strlen(buf);
			vsnprintf(buf+len, sizeof(buf)-len, sFmt , ap);

			len = strlen( buf );
			snprintf( buf+len, sizeof(buf)-len, "%s", "\n" );

			write( fd, buf, strlen(buf));
			
		      close( fd );		
		}
		
		va_end( ap );
	}

	void LogShmQueue :: Init()
	{	
		try
		{
			_shm = new  Shm( logShmQueuekey, logShmQueueSize, 0666 );

			_shm.Init();
		}
		catch( MemException &e )
		{
			WriteOwnLog("%s(%d) %s", __func__, __LINE__, e.GetMsg() );
		}
		catch( ... )
		{
			WriteOwnLog("%s(%d) %s", __func__, __LINE__, "Unknow error" );
		}
	}
	
}

