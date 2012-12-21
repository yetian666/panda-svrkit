#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <pthread.h>

#include "iLogShmQueue.h"
#include "iShm.h"
#include "iMagicNum.h"
#include "iException.h"
#include "iTerminalColor.h"

using namespace unistdext;
using namespace stdext;

namespace Comm
{
	LogShmQueue :: LogShmQueue():_shm(NULL), _ptHeader(NULL)
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
		//init shm
		try
		{
			_shm = new  Shm( logShmQueuekey, logShmQueueSize, 0666 );

			_shm.Init();
		}
		catch( MemException &e )
		{
			WriteOwnLog("%s(%d) %s", __func__, __LINE__, e.GetMsg() );
			throw e;
		}

		//init shm queue head
		_ptHeader = (LogShmQueueHead_t*)_shm.GetShmAddr();

		_ptHeader->hMainVer = LogShmQueue_MainVer;
		_ptHeader->hSubVer = LogShmQueue_SubVer;
		_ptHeader->iMagicNum = LogShmQueue_HeadMagicNum;
		_ptHeader->iHeadPos = 0;
		_ptHeader->iTailPos = 0;
		_ptHeader->iQueueSize = 0;
		_ptHeader->iFlag = LogShmQueue_FlagOK;

		_ptHeader->sData = (char*)_ptHeader +sizeof(LogShmQueueHead_t);
		
	}

	/**
	 * buf format: char(STX)+short(len)+data+char(ETX)
	 * push will modify head of shmQueue
	*/
	int LogShmQueue::Push(const char * pcBuf, const int iBufLen)
	{
		if( _shm == NULL || _ptHeader == NULL )
		{
			throw MemException(ERR_LogShmQueue_ShmOrHeadNULL, "LogShmQueue not inited or corrupted", __func__,
				__FILE__, __LINE__ );
		}
			
		if( _ptHeader->hMainVer != LogShmQueue_MainVer || _ptHeader->hSubVer != LogShmQueue_SubVer || 
			_ptHeader->iFlag != LogShmQueue_FlagOK || _ptHeader->iMagicNum != LogShmQueue_HeadMagicNum )
		{
			WriteOwnLog("%s:%s(%d)"TnClRED"logshmqueue head not correct mainver %d, sub ver %d, iFlag %d, MagicNum 0x%x"TnClEND, __FILE__, __func__, __LINE__,
				_ptHeader->hMainVer, _ptHeader->hSubVer, _ptHeader->iFlag, _ptHeader->iMagicNum );
			
			Reset();
		}
		
		int iHeadPos = _ptHeader->iHeadPos;
		int iRoom = _ptHeader->iTailPos - iHeadPos;

		if( iRoom < 0 )
			iRoom = _ptHeader->iQueueSize - iRoom;

		
		
	}

	void LogShmQueue::Reset()
	{
		WriteOwnLog(TnClRED"Reset the logshmqueue"TnClEND);

		if( _shm != NULL )
			free _shm;
		Init();
	}
	
}

