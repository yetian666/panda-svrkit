#pragma once
#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

#include "../../../proj_root.h"

using namespace std;

namespace google {
namespace protobuf {

namespace compiler {

	bool GeneratorRcfServiceDefFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd );
	
	bool GeneratorRcfMakefile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd );

	bool GeneratorRcfSimpleFile( const string& sTFilePath, const string& sOutputFilePath, 
		const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd );

}}}

