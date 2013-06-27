include ../PROJ_ROOT

INCLUDES = -I/usr/local/include -I$(PROJ_ROOT)/comm -I/usr/local/mysql/include/ 
LIBS = -L/usr/local/lib/ 

LIBDIR = /usr/local/lib

CPP = ccache g++

MAKEDEPEND = gcc -MM

CPPFLAGS = -Wall -g -DUSE_THREADS

OUTPUT = libcomm.a

SRCS = $(wildcard *.cpp utils/*.cpp core/file/*.cpp core/log/*.cpp  core/concurrent/*.cpp dao/*.cpp base/*.cpp base/stdext/*.cpp base/unistdext/*.cpp)

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
