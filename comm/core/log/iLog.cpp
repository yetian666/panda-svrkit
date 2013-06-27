#include <string>
#include <time.h>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/thread/mutex.hpp>

#include "iLogger.h"

#include "utils/iString.h"

#include "iLog.h"

using std::string;

#define COMMLOGMSG( loglevel, fm)  \
do{ \
	va_list ap;\
	va_start( ap, fm );\
	CheckLogName(); \
	Logger::getInstance ()->print(loglevel, fm, ap); \
	va_end( ap );\
}while(0)

namespace Comm
{
	static string GetLogName( int interval )
	{
		char logName[64] = {0};
		
		time_t tt = time( NULL );  
		struct tm temp;

		tt = ( tt / interval ) * interval;
		struct tm *curtime = localtime_r( &tt, &temp );
		int year = 1900 + curtime->tm_year;
		int month = curtime->tm_mon + 1;
		int day = curtime->tm_mday;
		int hour = curtime->tm_hour;
		int minute = curtime->tm_min;
		int second = curtime->tm_sec;

		if( interval >= 3600 )
		{
			snprintf( logName, sizeof(logName), "%04d%02d%02d%02d.log", year, month, day, hour );
		} else {
			snprintf( logName, sizeof(logName), "%04d%02d%02d%02d%02d%02d.log", year, month, day, hour, minute, second );
		}

		return string( logName );
	}


	static void CheckLogName()
	{
		static boost::mutex mx;
		boost::mutex::scoped_lock scopedLock(mx);

		std::string logName = GetLogName( 3600 );
		
		if( logName != LOGGER->getLogFile() )
		{
			LOGGER->setLogFile( logName );
		}
	}
	
	void OpenLogfile( const char* moduleName, const char *logPath )
	{
		LOGGER->setDebugLevel (MAX_LEVEL);
		LOGGER->setMoudleName( moduleName );
		LOGGER->setLogPath( logPath );
		LOGGER->setLogFile( GetLogName(3600) );
		
	}

	void SetLogSessionId( const unsigned int uin )
	{
		LOGGER->setSessionId( Comm::UIntToStr(uin) );
	}

	void SetLogSessionId( const std::string &id )
	{
		LOGGER->setSessionId( id );
	}

	void LogInfo(const char* sFormat, ...)
	{
		COMMLOGMSG( LOW_LEVEL, sFormat);
	}

	void LogErr(const char* sFormat, ...)
	{
		COMMLOGMSG( MEDIUM_LEVEL, sFormat);
	}
	void LogDebug(const char* sFormat, ...)
	{
		COMMLOGMSG( HIGH_LEVEL, sFormat);
	}
}

