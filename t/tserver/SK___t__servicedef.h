#pragma once

#include <RCF/Idl.hpp>

#include "__t__.pb.h"

RCF_BEGIN(__T__ServiceDef, "__T__ServiceDef")

	RCF_METHOD_R1(int, SKGetMetainfo, std::string&);

	RCF_METHOD_R2(int, SKEcho, const std::string&, std::string&);
	
__T_MOTHOD_P__

RCF_END(__T__ServiceDef);

