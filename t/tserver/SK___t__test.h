#pragma once
#include <string>
#include <stdio.h>
#include "iComm.h"

class __T__Test
{
public:
	typedef int (__T__Test::*TestFunc_t)(Comm::OptionMap& );
	typedef struct tagName2Func
	{
		std::string sFuncName;
		TestFunc_t tFunc;
		const std::string sOptionStr;
		const std::string sUsage;
	}Name2Func_t;

public:
	__T__Test(){}
	~__T__Test(){}

public:
	virtual int SKGetMetainfo( Comm::OptionMap& optMap)
	{
		printf(TnClRED"%s unimplemented"TnClEND" \n"
			"\t"TnClLIGHT_BLUE"please implement it in __T__TestImpl and call __T__Clent::%s in it"TnClEND"\n\n",
			__func__, __func__);
		return -1;
	}

	virtual int SKEcho( Comm::OptionMap& optMap )
	{
		printf(TnClRED"%s unimplemented"TnClEND" \n"
			"\t"TnClLIGHT_BLUE"please implement it in __T__TestImpl and call __T__Clent::%s in it"TnClEND"\n\n",
			__func__, __func__);
		return -1;
	}

__T_MOTHOD_P__

public:
	static const Name2Func_t* GetName2Func()
	{
		static Name2Func_t name2func[] ={
			{"SKGetMetainfo", &__T__Test::SKGetMetainfo, "c:f:u:", "-u <uin>"},
			{"SKEcho", &__T__Test::SKEcho, "c:f:u:", "-u <uin>"},
__T_TEST_MOTHOD_P__
			{"", NULL,"",""}
		};

		return name2func;
	}
	
};

