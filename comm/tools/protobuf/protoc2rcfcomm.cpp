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

	bool GeneratorRcfServiceDefFile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd ) 
	{
		//generator sk_servicedef.h
		string sServiceDefTemplateFileName = PROJ_ROOT"/t/tserver/SK___t__servicedef.h";
		string sServiceDefOutputFileName = "SK___t__servicedef.h";

		boost::algorithm::replace_all(sServiceDefOutputFileName, "__t__", sFileBaseName);
	
		ifstream in(sServiceDefTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << sServiceDefTemplateFileName<< " Error opening input stream" << endl;
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
			sRcfMethods += "\tRCF_METHOD_R2(int, "+string(md->name())+", const "+md->input_type()->name()+"&, std::string&);";

			if( j != sd->method_count()-1) 
			{
				sRcfMethods+="\n\n";
			}

			printf("method %d , name %s,  input_type %s, output_type %s\n",
				j, md->name().c_str(), md->input_type()->name().c_str(), 
				md->output_type()->name().c_str());
		}

		boost::algorithm::replace_all(sBuf, "__T_MOTHOD_P__", sRcfMethods);

		cout<<__func__<<endl;

		out.write( sBuf.c_str(), sBuf.size() );

		return true;
	}


	bool GeneratorRcfMakefile( const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd )
	{
		string sServiceTemplateFileName = PROJ_ROOT"/t/tserver/makefile";
		string sServiceOutputFileName = "makefile";

		boost::algorithm::replace_all(sServiceOutputFileName, "__t__", sFileBaseName);

		ifstream in(sServiceTemplateFileName.c_str());
		if( !in ) 
		{
			cerr << sServiceTemplateFileName<< " Error opening input stream" << endl;
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

	bool GeneratorRcfSimpleFile( const string& sTFilePath, const string& sOutputFilePath, 
		const string& sFileBaseName, const string& sServiceName, const ServiceDescriptor* sd )
	{
		string sServiceTemplateFileName = sTFilePath;
		string sServiceOutputFileName = sOutputFilePath;

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

}}}
