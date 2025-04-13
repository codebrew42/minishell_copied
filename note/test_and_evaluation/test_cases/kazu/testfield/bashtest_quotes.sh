#!/bin/bash

title()
{
	echo "-----------"
	echo test $1
	echo "-----------"
}

title 1
echo ""
echo $?

title 2
echo ''
echo $?

title 3
echo "hello 'world' !"
echo $?

title 4
echo 'hello "world" !'
echo $?

title 5
echo 'hello 'world' !'
echo $?

title 6
echo "hello "world" !"
echo $?


title 7
echo "$PATH"
echo $?

title 8
echo '$PATH'
echo $?

# with and without files
title 9
echo '*.c'
echo $?

title 10
echo "*.c"
echo $?

title 11
echo '*.py'
echo $?

title 12
echo "*.py"
echo $?

title 13
echo *.c
echo $?
