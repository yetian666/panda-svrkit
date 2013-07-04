include ../../PROJ_ROOT

rcf_dir = $(PROJ_ROOT)/thirdparty/RCF

INCLUDES = -I/usr/local/include/ -I$(PROJ_ROOT)/comm -I$(rcf_dir)/include -I/usr/local/mysql/include -I$(PROJ_ROOT)/douniu/comm

LIBDIR = /usr/local/lib 

rcf_LIBS = $(rcf_dir)/libRCF.a


LIBS = -lpthread -lprotobuf  -L/usr/local/lib/ -I$(PROJ_ROOT)/comm -lboost_system $(PROJ_ROOT)/comm/libcomm.a -lboost_date_time  $(rcf_LIBS) -lboost_filesystem -L/usr/local/mysql/lib/ -lmysqlclient $(PROJ_ROOT)/douniu/comm/libdncomm.a

CPP = ccache g++ -DRCF_USE_PROTOBUF
LIBTOOL = libtool --mode=link --tag=CXX

CPPFLAGS = -Wall -g  -Werror 

OUTPUT := __t__ __t__cli_tool lib__t__cli.a __t__stresstest

all: proto $(OUTPUT) 

proto:
	protoc --cpp_out ./ __t__.proto -I$(PROJ_ROOT)/comm/ -I. -I/usr/local/include/ -I$(PROJ_ROOT)/douniu/comm/

.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^ 

.cc.o: %.cc
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^

__t__: __t__.pb.o __t__main.o __t__serviceimpl.o SK___t__service.o 
	$(CPP) -o $@ $^	 $(LIBS)

__t__cli_tool: __t__.pb.o __t__client.o __t__cli_tool.o SK___t__clientproxy.o __t__testimpl.o
	$(CPP) -o $@ $^ $(LIBS)

__t__stresstest: __t__.pb.o __t__stresstest.o SK___t__clientproxy.o __t__client.o 
	$(CPP) -o $@ $^ $(LIBS)

lib__t__cli.a: __t__.pb.o __t__client.o SK___t__clientproxy.o 
	ar -r $@ $^

clean:
	rm -f *.o $(OUTPUT) 
