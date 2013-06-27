#pragma once
#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

using namespace std;


namespace google {
namespace protobuf {

namespace compiler {

	class RcfClientGenerator : public CodeGenerator
	{
	public:
		RcfClientGenerator();
		virtual ~RcfClientGenerator();
		
	public:
		bool Generate(const FileDescriptor* file,
                        const string& parameter,
                        OutputDirectory* output_directory,
                        string* error) const;

	private:

		bool GeneratorRcfClientHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfClientCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;
		
		bool GeneratorRcfClientImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfClientImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;

		bool GeneratorRcfClientConfFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const;
	};

}}}
