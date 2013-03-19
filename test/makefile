include ../PROJ_ROOT

casocklib_dir = $(PROJ_ROOT)/thirdparty/casocklib/src
rcf_dir = $(PROJ_ROOT)/thirdparty/RCF


tinyxml_INCLUDE = $(PROJ_ROOT)/thirdparty/tinyxml

INCLUDES = -I$(casocklib_dir) -I/usr/local/include/ -I$(PROJ_ROOT)/douniu/comm -I$(PROJ_ROOT)/comm -I$(rcf_dir)/include -I$(tinyxml_INCLUDE)

LIBDIR = /usr/local/lib 

#casocklib_LIBS = -lcasproasioclient -lcassioclient -lcasproasioserver -lcassioserver  $(casocklib_dir)/casock/rpc/asio/protobuf/server/.libs/libcasrpcaiopbserver.a $(casocklib_dir)/casock/rpc/asio/protobuf/client/.libs/libcasrpcaiopbclient.a $(casocklib_dir)/casock/util/.libs/libcasutil.a

casocklib_LIBS = $(casocklib_dir)/casock/util/.libs/libcasutil.a

rcf_LIBS = $(rcf_dir)/libRCF.a


tinyxml_dir = $(PROJ_ROOT)/thirdparty/tinyxml
tinyxml_LIBS = $(tinyxml_dir)/libtinyxml.a

LIBS = -lpthread -lprotobuf  -L/usr/local/lib/ -lboost_system $(PROJ_ROOT)/comm/libcomm.a -lboost_date_time -lboost_filesystem

CPP = ccache g++ -DRCF_USE_PROTOBUF
CC = ccache gcc 

LIBTOOL = libtool --mode=link --tag=CXX

CPPFLAGS = -Wall -g 
CFLAGS = -Wall -g

OUTPUT := testClientConfig testTinyXml testPosixRegex

all: $(OUTPUT) 

.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^ 

.cc.o: %.cc
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^

.c.o: %.c
	$(CC) $(CFLAGS) -c $^

testClientConfig: testClientConfig.o
	$(CPP) -o $@ $^ $(LIBS)

testTinyXml:testTinyXml.o
	$(CPP) -o $@ $^ $(tinyxml_LIBS) 

testPosixRegex:testPosixRegex.o
	$(CC) -o $@ $^

clean:
	rm -f *.o $(OUTPUT) 
