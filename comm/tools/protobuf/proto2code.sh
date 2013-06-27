#!/bin/sh

if [ $# != 1 ]
then
	echo "	usage:$0 server_port";
	echo "	./$0 10001"
	exit
fi

PROJ_ROOT=/home/douniu/dnproj

protoc2rcfservice ./*.proto --rcf_out ./ -I ${PROJ_ROOT}/douniu/comm -I. -I/usr/local/include/
protoc2rcfclient ./*.proto --rcf_out ./ -I ${PROJ_ROOT}/douniu/comm -I. -I/usr/local/include/
protoc2rcftest ./*.proto --rcf_out ./ -I ${PROJ_ROOT}/douniu/comm -I. -I/usr/local/include/
protoc --cpp_out ./ ./*.proto -I${PROJ_ROOT}/douniu/comm/ -I. -I/usr/local/include/ 

sed -i "s/10001/$1/" *main.cpp
sed -i "s/10001/$1/" *_cli.conf
sed -i "s/10001/$1/" *stresstest.cpp

make
