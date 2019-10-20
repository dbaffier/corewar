#!/bin/bash

while i < 10000; do
./corewar -n -1 champ/gateau.cor -d $i > a
./corewar_zaz champ/gateau.cor -d $i > b
diff a b
if echo $?
	exit
