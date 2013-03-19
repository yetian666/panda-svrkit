#pragma once

#include <sys/time.h>

namespace Comm
{
	class RunTime
	{

	public:
		RunTime();

		~RunTime();

		//return with ms
		int GetFuncRunTime();


	private:
		timeval _tTimeBegin;
		timeval _tTimePrev;
	};
}