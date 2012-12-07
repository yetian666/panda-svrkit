#pragma once

#include <sstream>
#include <iostream>
#include <string>

class Exception
{
public:

	Exception( const int iErrno, const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine = 0);
	
	Exception( const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine =0 );

	~Exception();
	
	const string what();

	const string GetErrMsg();

	const string GetMsg(); 
	
protected:
	int _iErrNo;
	string _sErrMsg;
	string _sFile;
	string _sFunc;
	int _iLine;
};


class IOException : public Exception
{
public:
	IOException( const int iErrno, const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine = 0):
		Exception( iErrno, sErrMsg, sFunc, iLine ){}
	
	IOException( const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine =0 ):
		Exception( sErrMsg, sFunc, sFile, iLine ){}

	~IOException();
};

class MemException : public Exception
{
public:
	MemException( const int iErrno, const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine = 0):
		Exception( iErrno, sErrMsg, sFunc, iLine ){}
	
	MemException( const string sErrMsg, const string sFunc = "", const string sFile="", const int iLine =0 ):
		Exception( sErrMsg, sFunc, sFile, iLine ){}

	~MemException();
};
