#include "protoc2rcfclient.h"
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

	RcfClientGenerator::RcfClientGenerator()
	{}

	RcfClientGenerator::~RcfClientGenerator()
	{}
	
	bool RcfClientGenerator::GeneratorRcfClientHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceDefTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__clientproxy.h";
		string sServiceDefOutputFileName = "SK___t__clientproxy.h";

		boost::algorithm::replace_all(sServiceDefOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceDefTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << sServiceDefTemplateFileName<<"Error opening input stream" << endl;
			return false;
		}

		if( access(sServiceDefOutputFileName.c_str(), 04 ) ==0 )
		{
			cout<<sServiceDefOutputFileName.c_str()<<" has existed, skip~~~~~"<<endl;
			return false;
		}

		ofstream out(sServiceDefOutputFileName.c_str());

		char pcBuf[32*1024];
		 
		memset(pcBuf, 0, sizeof(pcBuf) );
		in.read(pcBuf, sizeof(pcBuf));
		string sBuf = pcBuf;

		boost::algorithm::replace_all(sBuf, "__t__", sFileBaseName);
		
		boost::algorithm::replace_all(sBuf, "__T__", sServiceName);

		string sRcfMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);

			string sTFunc = "        int %s( __T__RcfClinet& rcfClient, \n"
			"               const unsigned int& iHeadUin,\n"
			"               const %s& request, \n"
			"               %s& response);\n\n";

			char pcMethod[2*1024];
			
			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTFunc.c_str(), md->name().c_str(), 
				md->input_type()->name().c_str(), md->output_type()->name().c_str());
				
			sRcfMethods += pcMethod;

		}
		
		boost::algorithm::replace_all(sRcfMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sRcfMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfClientGenerator::GeneratorRcfClientCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{

		string sTOuterFunc = "int __T__ClientProxy :: %s( __T__RcfClinet& rcfClient, \n"
			"               const unsigned int& iHeadUin,\n"
			"               const %s & request, \n"
			"               %s & response)\n"
			"{\n"
			"       int ret = 0;\n"
			"       std::string resp;\n"
			"       try\n"
			"       {\n"
			"               ret = rcfClient.%s( request, resp);\n"
			"       }\n"
			"       catch(const RCF::Exception & e)\n"
			"       {\n"
			"               _errmsg = \"Caught exception:\" + e.getError().getErrorString();\n"
			"               return -1001;\n"
			"       }\n"
			"\n"
			"       if( response.ParseFromString(resp) ==false) \n"
			"       {\n"
			"               _errmsg = response.GetTypeName()+\":\"+response.InitializationErrorString();\n"
			"               return -1001;\n"
			"       }\n"
			"\n"
			"       _errmsg = response.baseresponse().errmsg();\n"
			"\n"
			"       return ret;\n"
			"}\n"
			"\n";

		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__clientproxy.cpp";
		string sServiceOutputFileName = "SK___t__clientproxy.cpp";

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
			snprintf(pcMethod, sizeof(pcMethod), sTOuterFunc.c_str(), md->name().c_str(), 
				md->input_type()->name().c_str(), md->output_type()->name().c_str(),
				md->name().c_str());

			sOuterMethods += pcMethod;
		}

		boost::algorithm::replace_all(sOuterMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
		
	}
	
	bool RcfClientGenerator::GeneratorRcfClientImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__client.h";
		string sServiceOutputFileName = "__t__client.h";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << sServiceTemplateFileName<<" Error opening input stream" << endl;
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

			sOuterMethods += "\tint "+string(md->name())+"(const unsigned int& iHeadUin /*Add your args here*/);\n\n";
		}

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfClientGenerator::GeneratorRcfClientImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{	
		string sTOuterFunc = "int __T__Client :: %s(const unsigned int& iHeadUin /*Add your args here*/)\n"
			"{\n"
			"       int ret = 0;\n"
			"       Comm::Endpoint ep;\n"
			"       ret = _poConfig->GetEndpointBySect( GetSectByUin(iHeadUin), ep);\n"
			"\n"
			"       if( ret != COMM_OK )\n"
			"       {\n"
			"               LogErr(\"ERR: %%s(%%d) uin[%%u] errmsg[%%s], ret[%%d]\", __func__, __LINE__, iHeadUin, _poConfig->GetLastErrMsg().c_str(), ret );\n"
			"               _errmsg = _poConfig->GetLastErrMsg();\n"
			"               return -1;\n"
			"       }\n"
			"\n"
			"       %s req;\n"
			"       %s resp;\n"
			"\n"
			"       SetBaseRequest( iHeadUin, *(req.mutable_baserequest()) );\n"
			"\n"
			"       /*TODO:Add your request process code here*/\n\n"
			"       LogErr(TnClRED\"%%s uncompleted\"TnClEND\",\"\n"
			"		\"\\t\"TnClLIGHT_BLUE\"please complete it in __T__Clent::%%s\"TnClEND\"\",\n"
			"		__func__, __func__);\n"
			"\n"
			"       RCF::RcfInitDeinit rcfInit;\n"
			"       RcfClient<__T__ServiceDef> rcfClient( RCF::TcpEndpoint(ep.GetIp(), ep.GetPort()) );\n"
			"\n"
			"       __T__ClientProxy proxyClt;\n"
			"\n"
			"       ret = proxyClt.%s( rcfClient, iHeadUin, req, resp);\n"
			"\n"
			"       if( ret!=COMM_OK )\n"
			"       {\n"
			"               LogErr(\"ERR: %%s(%%d) uin[%%u] errmsg[%%s], ret[%%d]\",  __func__, __LINE__, iHeadUin, proxyClt.GetLastErrMsg().c_str(), ret );\n"
			"               _errmsg = proxyClt.GetLastErrMsg();\n"
			"               return -1;\n"
			"       }\n\n"
			"       _errmsg = resp.baseresponse().errmsg().c_str();\n"
			"\n"
			"       /*TODO:Add your response process code here*/\n\n"
			"       return resp.baseresponse().ret();\n"
			"}\n"
			"\n";

		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__client.cpp";
		string sServiceOutputFileName = "__t__client.cpp";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << sServiceTemplateFileName<<" Error opening input stream" << endl;
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
			snprintf(pcMethod, sizeof(pcMethod), sTOuterFunc.c_str(), md->name().c_str(), md->input_type()->name().c_str(),
				md->output_type()->name().c_str(), md->name().c_str() );

			sOuterMethods += pcMethod;
		}

		boost::algorithm::replace_all(sOuterMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
		
	}

	bool RcfClientGenerator::GeneratorRcfClientConfFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t___cli.conf";
		string sServiceOutputFileName = "__t___cli.conf";

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

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}
		
	bool RcfClientGenerator::Generate(const FileDescriptor * file, const string & parameter, OutputDirectory* output_directory, string * error) const
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
			
			GeneratorRcfClientHFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfClientCppFile( sFileBaseName, sServiceName, sd );
			
			GeneratorRcfClientImplHFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfClientImplCppFile( sFileBaseName, sServiceName, sd );

			GeneratorRcfClientConfFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfMakefile( sFileBaseName, sServiceName, sd );

			
		}
		
		return true;
	}
	
}}}


int main(int argc, char* argv[]) {

  google::protobuf::compiler::CommandLineInterface cli;
  cli.AllowPlugins("protoc-");

  // Proto2 rcfservice
  google::protobuf::compiler::RcfClientGenerator generator;
  cli.RegisterGenerator("--rcf_out", &generator,
                        "Generate rcf service header and source.");

  return cli.Run(argc, argv);
}


