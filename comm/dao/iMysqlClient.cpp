#include "iComm.h"
#include "iMysqlClient.h"
#include <errmsg.h>

using namespace std;

namespace Comm
{
	MysqlClient::MysqlClient(const char * pcIp, const int & iPort, const char * pcUser, const char * pcPwd, const char * pcDB)
	{
		_sIp = pcIp;
		_iPort = iPort;
		_sUser = pcUser;
		_sPwd = pcPwd;
		_sDB = pcDB;
		
		_pstMysql = NULL;
		_pstResult = NULL;

		Connect();
	}

	MysqlClient::~MysqlClient()
	{
		if( _pstResult!=NULL )
		{
			mysql_free_result(_pstResult);
			_pstResult = NULL;
		}

		if( _pstMysql!=NULL )
		{
			mysql_close( _pstMysql );
			_pstMysql = NULL;
		}
	}

	int MysqlClient::Connect()
	{
		if( _pstMysql!=NULL )
		{
			mysql_close( _pstMysql );
			_pstMysql = NULL;
		}
		
		_pstMysql = mysql_init( NULL );

		if( NULL != _pstMysql )
		{
			int iTimeOut = 200;
			
			mysql_options( _pstMysql, MYSQL_OPT_CONNECT_TIMEOUT, (char*)&iTimeOut );
			mysql_options( _pstMysql, MYSQL_OPT_READ_TIMEOUT, (char*)&iTimeOut  );

			bool reconnect = true;
			mysql_options( _pstMysql, MYSQL_OPT_RECONNECT, (char*)&reconnect );

			if( NULL == mysql_real_connect( _pstMysql, _sIp.c_str(), _sUser.c_str(), _sPwd.c_str(), _sDB.c_str(), _iPort, NULL, 0 ) )
			{
				_sErrMsg= string("ERR: mysql_real_connect fail, ") + mysql_error( _pstMysql );

				LogErr("ERR %s(%d) mysql_real_connect %s", __func__, __LINE__, _sErrMsg.c_str() );

				mysql_close( _pstMysql );

				_pstMysql = NULL;
				return -1;
			}
		}
		
		return 0;
	}


	int MysqlClient::Query(const char * pcSql)
	{
		if(_pstMysql == NULL)
		{
			return -1;
		}
			
		int ret = mysql_query( _pstMysql, pcSql );

		if( CR_SERVER_LOST == ret || CR_SERVER_GONE_ERROR == ret )
		{
			if( 0 == mysql_ping( _pstMysql ) )
			{
				ret = mysql_query( _pstMysql, pcSql );
			}
		}

		if( 0 != ret )
		{
			_sErrMsg= string("ERR: mysql_query fail, ret ") +Comm::TypeToStr(ret)+
				" , mysql errno "+Comm::TypeToStr( mysql_errno( _pstMysql) )+
				string(", ")+mysql_error( _pstMysql );
		}

		if( _pstResult!=NULL )
		{
			mysql_free_result(_pstResult);
			_pstResult = NULL;
		}

		_pstResult = mysql_store_result( _pstMysql );
		
		return ret;
	}

	int MysqlClient::GetNextRow(MYSQL_ROW * row)
	{
		if( _pstResult == NULL)
		{
			row = NULL;
			return -1;
		}

		*row = mysql_fetch_row(_pstResult);
		
		if( *row == NULL)
		{
			row = NULL;
			return -1;
		}

		return 0;
	}

	int MysqlClient::GetRowCnt()
	{
		if( _pstResult==NULL )
		{
			return 0;
		}

		return (int)mysql_num_rows(_pstResult);
	}
	
	string& MysqlClient::GetLastErrMsg()
	{
		return _sErrMsg;
	}
}