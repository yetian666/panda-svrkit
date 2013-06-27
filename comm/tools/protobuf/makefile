include ../../../PROJ_ROOT

INCLUDES = -I/usr/local/include -I$(PROJ_ROOT)/comm -I/usr/local/mysql/include/ 

LIBS = -L/usr/local/lib/ -lpthread -lprotobuf -lprotoc

CPP = ccache g++

MAKEDEPEND = gcc -MM

CPPFLAGS = -Wall -g

OUT_DIR = $(PROJ_ROOT)/bin_debug/

OUTPUT = protoc2rcfservice protoc2rcfclient protoc2rcftest

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o )


all:$(OUTPUT)


.depend:
	$(MAKEDEPEND) $(SRCS) > $@

depend:
	rm .depend
	$(MAKE) .depend


$(OBJS):%.o:%.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(INCLUDES)

$(OUTPUT):$(OBJS)
	g++ protoc2rcfcomm.o  protoc2rcfservice.o -o protoc2rcfservice $(CPPFLAGS) $(INCLUDES) $(LIBS)
	g++ protoc2rcfcomm.o protoc2rcfclient.o -o protoc2rcfclient $(CPPFLAGS) $(INCLUDES) $(LIBS)
	g++ protoc2rcfcomm.o protoc2rcftest.o -o protoc2rcftest $(CPPFLAGS) $(INCLUDES) $(LIBS)

include .depend    
.PHONY:clean cleanall

clean:            
	rm -f $(OUTPUT) $(OBJS)

cleanall:
	rm .depend
	rm -f $(OUTPUT) $(OBJS)
