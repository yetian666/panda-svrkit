Flags = "-g -Wall"
CPP = ccache g++

all:
	${CPP} ${FLags} Server.cpp  -I../include -lpthread -oServer ../libRCF.a
	${CPP} ${FLags} Client.cpp  -I../include -lpthread -oClient ../libRCF.a
