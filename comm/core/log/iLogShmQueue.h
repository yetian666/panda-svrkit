#pragma once

#include <uinstd.h>

#include "iShm.h"

using namespace unistdext;
using namespace stdext;

namespace Comm
{
    class LogShmQueue
    {
    	public:
		LogShmQueue();

		~LogShmQueue();

		void Init();

		int Push(const char* pcBuf, const int iBufLen );

		int Pop( char* pcBuf );
		
	private:
		void WriteOwnLog(const char *sFmt, ...) __attribute__( (__format__( __printf__,1, 2)));

	private:
		Shm* _shm;
    };
}
