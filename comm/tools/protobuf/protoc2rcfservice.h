#pragma once
#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

using namespace std;


namespace google {
namespace protobuf {

namespace compiler {

	class RcfServiceGenerator : public CodeGenerator
	{
	public:
		RcfServiceGenerator();
		virtual ~RcfServiceGenerator();
		
	public:
		bool Generate(const FileDescriptor* file,
                        const string& parameter,
                        OutputDirectory* output_directory,
                        string* error) const;

	private:

		bool GeneratorRcfServiceHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfServiceCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;
		
		bool GeneratorRcfServiceImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfServiceImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfServiceConfFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfServiceMainFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

	};

}}}
