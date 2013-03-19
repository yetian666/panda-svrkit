#!/bin/sh
wget "http://www.python.org/ftp/python/2.7.3/Python-2.7.3.tgz"
wget "https://protobuf.googlecode.com/files/protobuf-2.4.1.tar.gz"
wget "http://ncu.dl.sourceforge.net/project/boost/boost/1.53.0/boost_1_53_0.tar.gz"

tar -xzvf *.tgz
tar -xzvf *.tar.gz

ln -s Python-2.7.3 Python
ln -s protobuf-2.4.1 protobuf
ln -s boost_1_53_0 boost

wget http://ncu.dl.sourceforge.net/project/tinyxml/tinyxml/2.6.2/tinyxml_2_6_2.tar.gz
wget http://prdownloads.sourceforge.net/tinycxx/tinycxx-samples-0.1.1.tar.gz
wget http://nchc.dl.sourceforge.net/project/tinycxx/tinycxx/0.1.1/tinycxx-0.1.1.tar.gz