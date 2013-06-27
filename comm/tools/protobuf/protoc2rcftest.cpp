#include "protoc2rcftest.h"
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

	RcfTestGenerator::RcfTestGenerator()
	{}

	RcfTestGenerator::~RcfTestGenerator()
	{}


	bool RcfTestGenerator::GeneratorRcfTestHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceDefTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__test.h";
		string sServiceDefOutputFileName = "SK___t__test.h";

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

		string sRcfMethods, sRcfTMethods;
		
		for( int j=0; j<sd->method_count(); j++ )
		{
			const MethodDescriptor *md = sd->method(j);

			string sTFunc = "\tvirtual int %s( Comm::OptionMap& optMap )\n"
				"\t{\n"
				"\t	printf(TnClRED\"%%s unimplemented\"TnClEND\" \\n\"\n"
				"\t		\"\\t\"TnClLIGHT_BLUE\"please implement it in __T__TestImpl and call __T__Clent::%%s in it\"TnClEND\"\\n\\n\",\n"
				"\t		__func__, __func__);\n"
				"\t	return -1;\n"
				"\t}\n\n";

			string sTTestFunc = "			{\"%s\", &__T__Test::%s, \"c:f:u:\", \"-u <uin> \"},\n";

			char pcMethod[2*1024];
			
			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTFunc.c_str(), md->name().c_str() );
				
			sRcfMethods += pcMethod;

			memset( pcMethod, 0, sizeof(pcMethod) );
			snprintf(pcMethod, sizeof(pcMethod), sTTestFunc.c_str(), md->name().c_str(), md->name().c_str() );
			
			sRcfTMethods+=pcMethod;

		}
		
		boost::algorithm::replace_all(sRcfMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sRcfMethods);

		boost::algorithm::replace_all(sRcfTMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_TEST_MOTHOD_P__", sRcfTMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}
	
	bool RcfTestGenerator::GeneratorRcfTestImplHFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__testimpl.h";
		string sServiceOutputFileName = "__t__testimpl.h";

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
			sOuterMethods += "\tvirtual int "+string(md->name())+"( Comm::OptionMap& optMap );\n\n";
		}

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}

	bool RcfTestGenerator::GeneratorRcfTestImplCppFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) const
	{	
		string sTOuterFunc = "int __T__TestImpl :: %s( Comm::OptionMap& optMap )\n"
			"{\n"
			"	unsigned int iUin = 0;\n"
			"\n"
			"	int ret = optMap.GetValue( 'u', &iUin);\n"
			"\n"
			"	if( ret!=COMM_OK )\n"
			"	{\n"
			"		printf(\"ERR: cant get uin, ret %%d\\n\", ret);\n"
			"		return ret;\n"
			"	}\n\n"
			"	__T__Client client;     \n"
			"\n"
			"	/*TODO:: Add your pack code here*/\n"
			"\n"
			"	printf(TnClRED\"%%s uncompleted\"TnClEND\" \\n\"\n"
			"		\"\\t\"TnClLIGHT_BLUE\"please complete it in __T__TestImpl and  __T__Clent::%%s\"TnClEND\"\\n\\n\",\n"
			"		__func__, __func__);\n"
			"\n"
			"	ret = client.%s(iUin /*TODO:Add your argvs here*/);\n"
			"\n"
			"	if(  ret !=COMM_OK)\n"
			"	{\n"
			"		printf(\"ERR: ret %%d errmsg %%s\\n\", ret, client.GetLastErrMsg().c_str() );\n"
			"		return ret;\n"
			"	}\n"
			"\n"
			"	printf(\"ret %%d errmsg %%s\\n\", ret, client.GetLastErrMsg().c_str() );\n"
			"\n"
			"	/*TODO:: Add your unpack code here*/\n"
			"\n"
			"	return 0;\n"
			"}\n\n";

		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/__t__testimpl.cpp";
		string sServiceOutputFileName = "__t__testimpl.cpp";

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
			snprintf(pcMethod, sizeof(pcMethod), sTOuterFunc.c_str(), md->name().c_str(), md->name().c_str() );

			sOuterMethods += pcMethod;
		}

		boost::algorithm::replace_all(sOuterMethods, "__T__", sServiceName);

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sOuterMethods);

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
		
	}
		
	bool RcfTestGenerator::Generate(const FileDescriptor * file, const string & parameter, OutputDirectory* output_directory, string * error) const
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
			
			GeneratorRcfTestHFile( sFileBaseName, sServiceName, sd );
			
			GeneratorRcfTestImplHFile( sFileBaseName, sServiceName, sd );
			GeneratorRcfTestImplCppFile( sFileBaseName, sServiceName, sd );

			GeneratorRcfSimpleFile( PROJ_ROOT"/t/tserver/__t__cli_tool.cpp", 
				"__t__cli_tool.cpp",
				sFileBaseName, sServiceName, sd );
			
			GeneratorRcfSimpleFile( PROJ_ROOT"/t/tserver/__t__stresstest.cpp", 
				"__t__stresstest.cpp",
				sFileBaseName, sServiceName, sd );

			
		}
		
		return true;
	}
	
}}}


int main(int argc, char* argv[]) {

  google::protobuf::compiler::CommandLineInterface cli;
  cli.AllowPlugins("protoc-");

  // Proto2 rcfservice
  google::protobuf::compiler::RcfTestGenerator generator;
  cli.RegisterGenerator("--rcf_out", &generator,
                        "Generate rcf service header and source.");

  return cli.Run(argc, argv);
}


