include ../PROJ_ROOT

INCLUDES = -I/usr/local/include -I$(PROJ_ROOT)/comm
LIBS = -L/usr/local/lib/

LIBDIR = /usr/local/lib

CPP = ccache g++

MAKEDEPEND = gcc -MM

CPPFLAGS = -Wall -g

OUTPUT = libcomm.a

SRCS = $(wildcard *.cpp utils/*.cpp core/file/*.cpp core/concurrent/*.cpp)

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
