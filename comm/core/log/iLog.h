#pragma once

namespace Comm
{
	void OpenLogfile( const char* moduleName, const char *logPath );

	void SetLogSessionId( const unsigned int uin );

	void SetLogSessionId( const std::string &id );

	void LogInfo(const char* sFormat, ...);

	void LogErr(const char* sFormat, ...);

	void LogDebug(const char* sFormat, ...);
}
