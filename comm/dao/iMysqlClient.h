#pragma once
#include <string>

#include <mysql.h>

namespace Comm
{
	class MysqlClient
	{
	public :
		MysqlClient(const char*pcIp, const int& iPort, const char* pcUser, const char* pcPwd, const char* pcDB);
		~MysqlClient();

		int Query(const char* pcSql);

		int GetNextRow( MYSQL_ROW* row );

		int GetRowCnt();

		std::string& GetLastErrMsg();

	protected:
		int Connect();
		
	private:
		MYSQL* _pstMysql;
		std::string _sIp;
		int _iPort;
		std::string _sUser;
		std::string _sPwd;
		std::string _sDB;
		MYSQL_RES* _pstResult;
		std::string _sErrMsg;
	};
}

