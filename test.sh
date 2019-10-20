#!/bin/bash

num='^[0-9]+$'
filename=$1

if ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ $2 =~ $num ]] || ! [[ $3 =~ $num ]] ; then
   echo "$0 [*.cor] [begin (0-9)] [end (0-9)]"
   exit 1
fi

make -j 8
if ! [[ test -eq 0 ]] ; then
	exit 1
fi

i=$2

while [ $i -le $3 ]
do
	./corewar -n -1 $filename -d $i > a
	./corewar_zaz $filename -d $i > b
	diff a b
	ret=$?
	if test $ret -eq 1 ; then
		echo Cycle: $i
		exit 1
	fi
	((i++))
done

exit 0
