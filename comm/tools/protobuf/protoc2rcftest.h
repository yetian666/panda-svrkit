#pragma once
#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

using namespace std;


namespace google {
namespace protobuf {

namespace compiler {

	class RcfTestGenerator : public CodeGenerator
	{
	public:
		RcfTestGenerator();
		virtual ~RcfTestGenerator();
		
	public:
		bool Generate(const FileDescriptor* file,
                        const string& parameter,
                        OutputDirectory* output_directory,
                        string* error) const;

		bool GeneratorRcfTestHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;
		
		bool GeneratorRcfTestImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfTestImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

	};

}}}
