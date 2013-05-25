#pragma once
#include <string>
#include <google/protobuf/compiler/code_generator.h>

using namespace std;
using namespace google::protobuf::compiler;

class RcfServiceGenerator : public CodeGenerator
{
public:
	RcfServiceGenerator();
public:
	bool Generate(const FileDescriptor * file, 
			const string & parameter, 
			GeneratorContext * generator_context, 
			string * error);

	private:
		string sTSKRcfServiceDefFile;
		string sTSKRcfServiceFileh;
		string sTSKRcfServiceFilecpp; 
		string sTRcfServiceImplFileh;
		string sTRcfserviceImplFilecpp;
		string sTRcfServiceMainFile;
};
