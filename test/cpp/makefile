all:
	protoc --cpp_out ./ ../test.proto -I../
	g++ -g -Wall -o testsvr testsvr.cpp test.pb.cc -lprotobuf
	g++ -g -Wall -o testcli testcli.cpp test.pb.cc -lprotobuf
