#!/bin/bash

num=0
count()
{
	echo "----------------------------------------------------------"
	printf "\e[36m$num\e[0m\n"
	printf "\e[36m---\e[0m\n"
	((num++))
}
exitst()
{
	echo $?
	count
}

count
echo *.c 
exitst
echo *.md
exitst

echo "test end"

