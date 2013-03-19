#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iServerControl.h"

namespace Comm
{
	int ForkAsDaemon()
	{
		int pid = fork();
		if( pid == 0 )
		{
			//become as session & process leader
			if( setsid() < 0 )
			{
				return -1;
			}

			//forbidden open terminal
			pid = fork();
			if( pid == 0 )
			{
				printf("Run as daemon ok.....\n");
				close(0);
				close(1);
				close(2);
				return 0;
			}
			
		}

		if( pid < 0 )
			return -1;
		
		exit(0);
		
		return 0;
	}

	void PrintHelp ( const char *server )
	{
		printf ( "%s <-i config file> [-d] [-v]\n", server );
		printf ( "Usage: \n");
		printf ( "    -i  <config file>  # configured file for index connection settings \n" ) ;
		printf ( "    -d                 # run as a daemon\n" );
		printf ( "    -v                 # print this screen\n" ) ;
		printf ( "\n" ) ;
		return;
	}

	int CommandLine ( int argc, char * const * argv, const char *server, int *daemon, char *configfile, const int buflen )
	{
		*daemon = 0;
		*configfile = '\0';

		if ( argc < 2 )
		{
			PrintHelp(server);
			return -1 ;
		}

		int c ;
		while ( (c = getopt ( argc, argv, "di:v" )) != EOF )
		{
			switch ( c )
			{
				case 'd' :
					*daemon = 1 ;
					break ;
				case 'i' :
					strncpy ( configfile, ::optarg, buflen );
					break ;
				case 'v' :
				case '?' :
					PrintHelp(server);
					return -1 ;
					break ;
				default :
					PrintHelp(server);
					return -1 ;
					break ;
			}
		}

		if( strlen(configfile) == 0 )
		{
			PrintHelp(server);
			return -1 ;
		}
		
		return 0 ;
	}
}
