#pragma once

#include <sstream>
#include <iostream>
#include <string>

namespace stdext
{
	class Exception
	{
	public:

		Exception( const int iErrno, const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine = 0);
		
		Exception( const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine =0 );

		Exception( const int iErrno, const std::string sFunc = "", const std::string sFile="", const int iLine =0 );

		~Exception();
		
		const std::string what();

		const std::string GetErrMsg();

		const std::string GetMsg(); 

		const int GetErrNo();
		
	protected:
		int _iErrNo;
		std::string _sErrMsg;
		std::string _sFile;
		std::string _sFunc;
		int _iLine;
	};


	class IOException : public Exception
	{
	public:
		IOException( const int iErrno, const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine = 0):
			Exception( iErrno, sErrMsg, sFunc, iLine ){}
		
		IOException( const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine =0 ):
			Exception( sErrMsg, sFunc, sFile, iLine ){}

		IOException( const int iErrno, const std::string sFunc = "", const std::string sFile="", const int iLine =0 ):
			Exception( iErrno, sFunc, sFile, iLine ){}

		~IOException();
	};

	class MemException : public Exception
	{
	public:
		MemException( const int iErrno, const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine = 0):
			Exception( iErrno, sErrMsg, sFunc, iLine ){}
		
		MemException( const std::string sErrMsg, const std::string sFunc = "", const std::string sFile="", const int iLine =0 ):
			Exception( sErrMsg, sFunc, sFile, iLine ){}
			
		MemException( const int iErrno, const std::string sFunc = "", const std::string sFile="", const int iLine =0 ):
			Exception( iErrno, sFunc, sFile, iLine ){}
			
		~MemException();
	};
}
