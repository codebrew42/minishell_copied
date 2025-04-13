#!/bin/bash

title()
{
	echo "-----------"
	echo test $1
	echo "-----------"
}

title 1
echo hello | cat
echo $?

title 2
env | cat | wc -l
echo $?

title 3
"" | cat | wc -l
echo $?

title 4
env | "" | wc -l
echo $?

title 5
env | cat | ""
echo $?

