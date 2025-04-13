#!/bin/bash

title()
{
	printf "\n\n\e[36m**********************************************************\e[0m\n"
	printf "\n\n\e[36m\t\t\t$*\e[0m\n\n"
	printf "\n\e[36m**********************************************************\e[0m\n"
	#echo "----------------------------------------------------------"
}

testjob()
{
	#printf "\e[36m$*\e[0m\n"
	echo $*
	printf "\e[36m---\e[0m\n"
	echo $* | bash; echo $?
	echo "----------------------------------------------------------"
}

line()
{
	echo "----------------------------------------------------------"
}

printf "\n\n\e[34m----------------------------------------------------------\e[0m\n"
printf "\e[34m\t\t\tbash test\e[0m\n"
printf "\e[34m----------------------------------------------------------\e[0m\n\n"

title basic

testjob 'ls'
testjob '/bin/ls'
testjob '/bin/ls -l'
testjob '/bin/echo hello'
testjob '/usr/bin/env'


title echo

testjob 'echo test'
testjob 'echo -n simple'
testjob 'echo -n -n -nnnn -nnnnm'
testjob 'echo -nnnn'
testjob 'echo -nnnn -nnnnm'
testjob "echo ''"
testjob 'echo ""'
testjob 'echo "\n \n \n"'
testjob 'echo "\n \n \\n"'
#testjob 'echo *.c'
#testjob 'echo *.md'

testjob 'echo "$HOME"'

#echo '$HOME'
testjob echo "'"'$HOME'"'"

#testjob 'echo $PATH'

#testjob 'echo $'PATH''
#testjob 'echo 'PATH'estjob 'echo $0''
#testjob 'echo 'PATH'estjob 'echo $0''

testjob 'cat xxx'

