
INCLUDES = -I/usr/local/include
LIBS = -L/usr/local/lib/

LIBDIR = /usr/local/lib

CPP = ccache g++

CPPFLAGS = -Wall -g

SRCS = $(wildcard *.cpp )

OBJS = $(SRCS:.cpp=.o )

OUTPUT = $(OBJS)

all:$(OUTPUT)


.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $^ 

clean:
	rm -f *.o 
