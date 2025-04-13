#!/bin/bash

title()
{
	echo "-----------"
	echo test $1
	echo "-----------"
}

title 1
echo && echo hi
echo $?

title 2
echo || echo hi
echo $?

title 3
echo hi && echo
echo $?

title 4
echo hi || echo
echo $?

title 5
echo hi && echo bye
echo $?

title 6
echo hi || echo bye
echo $?


# cat without parameter will read from input

#title 7
#cat | echo || ls
#echo $?

#title 8
#cat | echo && ls
#echo $?

#title 9
#cd .. && cd /
#echo $?
#
#title 10
#cd .. || cd /
#echo $?
#
#title 11
#cd / && cd ..
#echo $?
#
#title 12
#cd / || cd ..
#echo $?

title 13
pwd && ls
echo $?

title 14
pwd || ls
echo $?

title 15
pwd && pwd
echo $?

title 16
pwd || pwd
echo $?

title 17
pwd && ls && echo hi
echo $?

title 18
pwd || ls && echo hi
echo $?

title 19
pwd && ls || echo hi
echo $?

title 20
pwd || ls || echo hi
echo $?

title 21
ls || pwd
echo $?

title 22
pwd || ls
echo $?

title 23
ls && pwd
echo $?

title 24
pwd &&ls
echo $?

title 25
env && echo $VAR
echo $?

title 26
env || echo $VAR
echo $?

#title 27
#exit && echo "This should not print"
#echo $?
#
#title 28
#exit || echo "This should not print"
#echo $?


#bash: syntax error near unexpected token `;'
#title 29
#ls || ;
#echo $?

#bash: syntax error near unexpected token `;'
#title 30
#; || ls
#echo $?

#bash: syntax error near unexpected token `;'
#title 31
#ls && ;
#echo $?

#bash: syntax error near unexpected token `;'
#title 32
#; && ls
#echo $?

#bash: syntax error near unexpected token `newline'
#title 33
#ls || <
#echo $?

#bash: syntax error near unexpected token `newline'
#title 34
#ls && <
#echo $?

title 35
cat xxx || ls
echo $?

title 36
cat xxx && ls
echo $?

title 37
ls || cat xxx
echo $?

title 38
ls && cat xxx
echo $?

# with pipe

title 39
ls | cat || pwd
echo $?

title 38
ls | cat && pwd
echo $?

title 40
ls | cat xxx || pwd
echo $?

title 41
ls | cat xxx && pwd
echo $?

title 42
cat xxx | wc || pwd
echo $?

title 43
cat xxx | wc && pwd
echo $?

title 44
cat xxx || ls | wc && pwd
echo $?
