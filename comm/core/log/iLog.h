#pragma once

namespace Comm
{
	void OpenLogfile( const char* moduleName, const char *logPath );

	void SetLogSessionId( const unsigned int uin );

	void SetLogSessionId( const std::string &id );

	void LogInfo(const char* sFormat, ...) __attribute__( (__format__( __printf__,1, 2)));

	void LogErr(const char* sFormat, ...) __attribute__( (__format__( __printf__,1, 2)));

	void LogDebug(const char* sFormat, ...) __attribute__( (__format__( __printf__,1, 2)));
}
