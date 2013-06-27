#include "protoc2rcfservice.h"
#include "protoc2rcfcomm.h"

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/command_line_interface.h>

#include <boost/algorithm/string.hpp>
#include <unistd.h>

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

namespace google {
namespace protobuf {
namespace compiler {

	RcfServiceGenerator::RcfServiceGenerator()
	{}

	RcfServiceGenerator::~RcfServiceGenerator()
	{}

	bool RcfServiceGenerator::GeneratorRcfServiceHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		//generator sk_servicedef.h
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__service.h";
		string sServiceOutputFileName = "SK___t__service.h";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		string sOuterMethods, sInnerMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);
		
			sInnerMethods += "\tint "+string(md->name())+"( const "+md->input_type()->name()+"& request, std::string& strResponse);";

			sOuterMethods += "\tvirtual int "+string(md->name())+"( const "+md->input_type()->name()+"& request, "+md->output_type()->name()+"& response);";

			if( j != sd->method_count()-1) 
			{
				sInnerMethods+="\n\n";
				sOuterMethods+="\n\n";
			}
		}

		boost::algorithm::replace_all(sBuf, "__T_INNER_MOTHOD_P__", sInnerMethods);

		boost::algorithm::replace_all(sBuf, "__T_OUTER_MOTHOD_P__", sOuterMethods);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfServiceGenerator::GeneratorRcfServiceCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{	
		string sTInnerFunc = "int __T__Service :: %s(const %s& request, \n"
		"               std::string& strResponse)\n"
		"{\n"
		"	%s response;\n"
		"	BaseResponse* baseResp = response.mutable_baseresponse();\n"
		"\n"
		"	int ret = %s( request, response );\n"
		"\n"
		"	baseResp->set_ret( ret );\n"
		"	baseResp->set_errmsg( _errmsg );\n"
		"\n"
		"	if( response.SerializeToString( &strResponse ) == false )\n"
		"	{\n"
		"		LogErr(\"%%s(%%d)%%s %%s\",__func__, __LINE__, response.GetTypeName().c_str(), response.InitializationErrorString().c_str());\n"
		"		return -1001;\n"
		"	}\n"
		"\n"
		"	return ret;\n"
		"}\n";

		string sTOuterFunc = "int __T__Service :: %s(const %s& request, \n"
		"       %s& response)\n"
		"{\n"
		"	LogErr( \"ERR: %%s unimplemented\", __func__ );\n"
		"	return -1;\n"
		"}\n"
		"\n";

		//generator sk_servicedef.cpp
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__service.cpp";
		string sServiceOutputFileName = "SK___t__service.cpp";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		string sOuterMethods, sInnerMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);

			char pcMethod[2*1024];
			
			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTInnerFunc.c_str(), md->name().c_str(), 
				md->input_type()->name().c_str(), md->output_type()->name().c_str(),
				md->name().c_str());
		
			sInnerMethods += pcMethod;

			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTOuterFunc.c_str(), md->name().c_str(), 
				md->input_type()->name().c_str(), md->output_type()->name().c_str() );

			sOuterMethods += pcMethod;

			if( j != sd->method_count()-1) 
			{
				sInnerMethods+="\n\n";
				sOuterMethods+="\n\n";
			}
		}

		boost::algorithm::replace_all(sOuterMethods, "__T__", sServiceName);
		
		boost::algorithm::replace_all(sInnerMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_INNER_MOTHOD_P__", sInnerMethods);

		boost::algorithm::replace_all(sBuf, "__T_OUTER_MOTHOD_P__", sOuterMethods);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
		
	}
	
	bool RcfServiceGenerator::GeneratorRcfServiceImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__serviceimpl.h";
		string sServiceOutputFileName = "__t__serviceimpl.h";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		string sOuterMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);

			sOuterMethods += "\tint "+string(md->name())+"( const "+md->input_type()->name()+"& request, "+md->output_type()->name()+"& response);";

			if( j != sd->method_count()-1) 
			{
				sOuterMethods+="\n\n";
			}
		}

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfServiceGenerator::GeneratorRcfServiceImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{	
		string sTOuterFunc = "int __T__ServiceImpl :: %s(const %s& request,\n"
		"               %s& response)\n"
		"{\n"
		"	const BaseRequest* basereq = &request.baserequest();\n"
		"	SetLogSessionId( basereq->uin() );\n"
		"\n"
		"	LogDebug(\"uin %%u, deviceid %%s, deviceType %%s\", \n"
		"		basereq->uin(), basereq->deviceid().c_str(), basereq->devicetype().c_str());\n"
		"\n"
		"	int ret = -1;\n"
		"\n"
		"	//TODO:: add method Impl here\n"
		"\n"
		"	LogErr(TnClRED\"%%s uncompleted\"TnClEND\",\"\n"
		"		\"\\t\"TnClLIGHT_BLUE\"please complete it in __T__ServiceImpl::%%s\"TnClEND\"\",\n"
		"		__func__, __func__);\n"
		"\n"
		"	_errmsg = TnClRED\"unimpliment method\"TnClEND ;\n"
		"	return ret;\n"
		"}\n";

		//generator sk_servicedef.cpp
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__serviceimpl.cpp";
		string sServiceOutputFileName = "__t__serviceimpl.cpp";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		string sOuterMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);

			char pcMethod[2*1024];

			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTOuterFunc.c_str(), md->name().c_str(), md->input_type()->name().c_str(), md->output_type()->name().c_str() );

			sOuterMethods += pcMethod;

			if( j != sd->method_count()-1) 
			{
				sOuterMethods+="\n\n";
			}
		}

		boost::algorithm::replace_all(sOuterMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
		
	}

	bool RcfServiceGenerator::GeneratorRcfServiceConfFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__.conf";
		string sServiceOutputFileName = "__t__.conf";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfServiceGenerator::GeneratorRcfServiceMainFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__main.cpp";
		string sServiceOutputFileName = "__t__main.cpp";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << "Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}
		
	bool RcfServiceGenerator::Generate(const FileDescriptor * file, const string & parameter, OutputDirectory* output_directory, string * error) const
	{
		//get file base name
		string sFileBaseName= file->name().substr(0, file->name().size() - strlen(".proto"));

		cout<<sFileBaseName<<endl;
		cout<<parameter<<endl;

		if(file->service_count() >1 )
		{
			cout<<"service count must less than one~~~~"<<endl;
			return false;
		}
		
		for ( int i=0; i<file->service_count(); i++ )
		{
			const ServiceDescriptor *sd = file->service(i);

			//get service name
			string sServiceName = sd->name();
			sServiceName = sServiceName.substr(0, sServiceName.size() - strlen("Service"));

			GeneratorRcfServiceDefFile( sFileBaseName, sServiceName, sd );
			
			GeneratorRcfServiceHFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfServiceCppFile( sFileBaseName, sServiceName, sd );
			
			GeneratorRcfServiceImplHFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfServiceImplCppFile( sFileBaseName, sServiceName, sd );

			GeneratorRcfServiceConfFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfServiceMainFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfMakefile( sFileBaseName, sServiceName, sd );

			
		}
		
		return true;
	}
	
}}}


int main(int argc, char* argv[]) {

  google::protobuf::compiler::CommandLineInterface cli;
  cli.AllowPlugins("protoc-");

  // Proto2 rcfservice
  google::protobuf::compiler::RcfServiceGenerator generator;
  cli.RegisterGenerator("--rcf_out", &generator,
                        "Generate rcf service header and source.");

  return cli.Run(argc, argv);
}


