#include <sstream>
#include "iException.h"

Exception :: Exception(const int iErrno, const string sFunc , const string sErrMsg, const string sFile , const int iLine )
{
	_iErrNo = iErrno;
	_sErrMsg = sErrMsg;
	_sFile = sFile;
	_sFunc = sFunc;
	_iLine = iLine;
}

Exception :: Exception(const string sErrMsg, const string sFunc , const string sFile , const int iLine )
{
	_sErrMsg = sErrMsg;
	_sFile = sFile;
	_sFunc = sFunc;
	_iLine = iLine;
}

Exception::~Exception(){}

const string Exception::what()
{		
	char buf[1024] = {0};
	if( _sErrMsg.empty() )
		return string( strerror_r(_iErrNo, buf , 1024) )

	return string( strerror_r(_iErrNo, buf , 1024))+" -> "+_sErrMsg;
}

const string Exception :: GetErrMsg()
{
	return what();
}

const string Exception :: GetMsg()
{	
	stringstream oss;
	oss<<_sFile<<":"<<_sFunc<<":"<<_iLine<<what();

	return oss.str();
}
