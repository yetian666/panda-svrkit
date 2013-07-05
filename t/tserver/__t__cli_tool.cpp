#include <string.h>

#include "iComm.h"

#include "SK___t__test.h"
#include "__t__testimpl.h"
#include "__t__client.h"

using namespace Comm;

void showUsage( const char * program )
{
	printf( "\nUsage: %s [-c <config>] [-f <func>] [-u <uin>]\n", program );

	const __T__Test::Name2Func_t * name2func = __T__Test::GetName2Func();

	for( int i = 0; i < 100; i++ )
	{
		const __T__Test::Name2Func_t * iter = &( name2func[i] );

		if( NULL == iter->tFunc ) break;

		printf( "\t-f %s %s\n", iter->sFuncName.c_str(), iter->sUsage.c_str() );
	}
	printf( "\n" );
	exit( 0 );
}

int main( int argc, char * argv[] )
{
	OpenLogfile("__t__cli_tool", "/home/sspace/log/error" );
	
	const char * func = NULL;
	const char * config = NULL;

	for( int i = 1; i < argc - 1; i++ )
	{
		if( 0 == strncmp( argv[i], "-c" , 2 ) )
		{
			config = argv[ ++i ];
		}
		if( 0 == strncmp( argv[i], "-f" , 2  ) )
		{
			func = argv[ ++i ];
		}
	}

	if( NULL == func ) showUsage( argv[0] );

	if( NULL != config )
	{
		__T__ClientConfig::GetDefault(config);
	}

	const __T__Test::Name2Func_t * target = NULL;

	const __T__Test::Name2Func_t * name2func = __T__Test::GetName2Func();

	for( int i = 0; i < 100; i++ )
	{
		const __T__Test::Name2Func_t * iter = &( name2func[i] );

		if( NULL == iter->tFunc ) break;

		if( 0 == iter->sFuncName.compare( func ) )
		{
			target = iter;
			break;
		}
	}

	if( NULL == target ) showUsage( argv[0] );

	Comm::OptionMap optMap( target->sOptionStr.c_str() );

	if( 0 != optMap.Parse( argc, argv ) ) showUsage( argv[0] );


	__T__Test::TestFunc_t testfunc = target->tFunc;
	
	__T__TestImpl testobj;

	if( 0 != ( testobj.*testfunc ) ( optMap ) ) showUsage( argv[0] );

	return 0;
}
