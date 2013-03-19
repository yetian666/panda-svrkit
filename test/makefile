include ../PROJ_ROOT

casocklib_dir = $(PROJ_ROOT)/thirdparty/casocklib/src
rcf_dir = $(PROJ_ROOT)/thirdparty/RCF

INCLUDES = -I$(casocklib_dir) -I/usr/local/include/ -I$(PROJ_ROOT)/douniu/comm -I$(PROJ_ROOT)/comm -I$(rcf_dir)/include

LIBDIR = /usr/local/lib 

#casocklib_LIBS = -lcasproasioclient -lcassioclient -lcasproasioserver -lcassioserver  $(casocklib_dir)/casock/rpc/asio/protobuf/server/.libs/libcasrpcaiopbserver.a $(casocklib_dir)/casock/rpc/asio/protobuf/client/.libs/libcasrpcaiopbclient.a $(casocklib_dir)/casock/util/.libs/libcasutil.a

casocklib_LIBS = $(casocklib_dir)/casock/util/.libs/libcasutil.a

rcf_LIBS = $(rcf_dir)/libRCF.a


LIBS = -lpthread -lprotobuf  -L/usr/local/lib/ -lboost_system $(PROJ_ROOT)/comm/libcomm.a -lboost_date_time -lboost_filesystem

CPP = ccache g++ -DRCF_USE_PROTOBUF
LIBTOOL = libtool --mode=link --tag=CXX

CPPFLAGS = -Wall -g 

OUTPUT := testClientConfig

all: $(OUTPUT) 

.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^ 

.cc.o: %.cc
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^


testClientConfig: testClientConfig.o
	$(CPP) -o $@ $^ $(LIBS)

clean:
	rm -f *.o $(OUTPUT) 
