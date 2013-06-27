#!/bin/sh
pwd=`env pwd`
read -p "	Do you want ot set $pwd as proj root:(Y/N)?" var
echo "";

if [ $var == Y ]
then 
	touch $pwd/PROJ_ROOT;
	echo "PROJ_ROOT = $pwd" >$pwd/PROJ_ROOT;
	echo -e "\033[32;49;1mCreate $pwd/PROJ_ROOT succ.\033[39;49;0m"

	touch $pwd/proj_root.h
	echo "#pragma once" >$pwd/proj_root.h
	echo "#define PROJ_ROOT \"$pwd\"" >>$pwd/proj_root.h
	echo -e "\033[32;49;1mCreate $pwd/proj_root.h succ.\033[39;49;0m"
else
	echo -e "\033[0;32;31mProj not inited!!! \033[39;49;0m"
fi
