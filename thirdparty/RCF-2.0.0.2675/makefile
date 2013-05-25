
INCLUDES = -I/usr/local/include -I./include
LIBS = -L/usr/local/lib/

LIBDIR = /usr/local/lib

CPP = ccache g++ -DRCF_USE_PROTOBUF

MAKEDEPEND = gcc -MM

CPPFLAGS = -Wall -g

OUTPUT = libRCF.a

SRCS = $(wildcard src/RCF/RCF.cpp )

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
	ar -r $@ $^

include .depend    
.PHONY:clean cleanall

clean:            
	rm -f $(OUTPUT) $(OBJS)

cleanall:
	rm .depend
	rm -f $(OUTPUT) $(OBJS)
