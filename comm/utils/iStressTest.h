#pragma once

namespace Comm
{
	typedef  int (*StressTestRPCCall)();

	int StressTestRun( int forkCount, StressTestRPCCall stressTestRpcCall, int timeout );
}