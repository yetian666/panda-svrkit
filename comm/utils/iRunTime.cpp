#include "iRunTime.h"

#include <string.h>
#include <unistd.h>

namespace Comm
{

	RunTime :: RunTime()
	{
		gettimeofday(&_tTimeBegin, NULL);
		gettimeofday(&_tTimePrev, NULL);
	}

	RunTime :: ~RunTime(){}
		
	int RunTime :: GetFuncRunTime()
	{
		struct timeval tNow;
		int septime = 0;

		gettimeofday( &tNow, NULL);

		septime = 1000000 * ( tNow.tv_sec - _tTimePrev.tv_sec ) + tNow.tv_usec - _tTimePrev.tv_usec;
		septime /= 1000;

		memmove( &_tTimePrev, &tNow, sizeof(struct timeval) );

		return septime;
	}
}