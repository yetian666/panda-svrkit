#pragma once
namespace Comm
{
	int ForkAsDaemon();

	int CommandLine ( int argc, char * const * argv, const char *server, int *daemon, char *configfile, const int buflen );
}