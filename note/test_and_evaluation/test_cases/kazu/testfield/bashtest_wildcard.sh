#!/bin/bash

#btest()
#{
#	echo "-----------"
#	input=$(printf "%q" "$*")
#	printf "%s\n" "$input"
#	#echo $input
#	echo "---"
#	echo $* | bash
#	echo "---"
#	echo $?
#}

title()
{
	echo "-----------"
	echo test $1
	echo "-----------"
}

# with and without files

title 1
echo '*.c'
echo $?

title 2
echo "*.c"
echo $?

title 3
echo '*.py'
echo $?

title 4
echo "*.py"
echo $?

title 5
echo *.c
echo $?

title 6
echo *test*
echo $?

title 7
echo *test*.sh
echo $?

title 8
echo t*st
echo $?

title 9
echo *.*
echo $?

title 10
echo *".c"
echo $?

title 11
ls *.*
echo $?
