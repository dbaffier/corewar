#!/bin/bash

num='^[0-9]+$'
filename=$1
filename2=$2
if ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ $3 =~ $num ]] || ! [[ $4 =~ $num ]] ; then
   echo "$0 [*.cor] [*.cor] [begin (0-9)] [end (0-9)]"
   exit 1
fi

make -j 8
if ! [[ test -eq 0 ]] ; then
	exit 1
fi

i=$3

while [ $i -le $4 ]
do
	printf "Testing cycle $i"\\r
	./corewar -n -1 $filename -n -2 $filename2 -d $i > a
	./corewar_zaz $filename $filename2 -d $i > b
	diff a b
	ret=$?
	if test $ret -eq 1 ; then
		exit 1
	fi
	((i++))
done

exit 0
