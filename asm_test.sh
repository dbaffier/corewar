#!/bin/bash

count=0
success=0
error=0
crash=0

for entry in "unitest_asm/err"/*.s
do
	count=$((count + 1))
	err=$(echo $(./asm $entry >&/dev/null ; echo $?))
	target=$(echo $entry | cut -f3 -d"/")
	if [ "$err" -eq 1 ]
	then
		success=$((success + 1))
		printf "%-40s\033[32m%40s\033[0m\n" $target "OK"
	elif [ "$err" -gt 1 ]
	then
		crash=$((crash + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target ">0"
	else
		error=$((error + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target "NO"
	fi
done

for entry in "unitest_asm/valid"/*.s
do
	count=$((count + 1))
	err=$(echo $(./asm $entry >&/dev/null ; echo $?))
	target=$(echo $entry | cut -f3 -d"/")
	if [ "$err" -eq 0 ]
	then
		success=$((success + 1))
		printf "%-40s\033[32m%40s\033[0m\n" $target "OK"
	elif [ "$err" -gt 1 ]
	then
		crash=$((crash + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target ">0"
	else
		error=$((error + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target "NO"
	fi
done

printf "\n\t\tnumber of test : $count\n"
printf "\t\tsuccess $success - error $error - crash $crash\n"
rm *.cor 2>&-
