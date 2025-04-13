## testers
- **&&** and **||** and **wildcards \*** are the bonus part.
- the test commands goes mostly in this order

## order
	1. builtins: echo -> cd -> pwd -> export -> unset -> env -> exit
	2. executables : ls -> 
	> **note:**check this 3
	3. with parenthesis : not sure, if we might handle this or not. 

```shell
echo && echo hi
echo || echo hi
echo hi && echo
echo hi || echo
echo hi && echo bye
echo hi || echo bye

cat | echo || ls
cat | echo && ls

cd .. && cd /
cd .. || cd /
cd / && cd ..
cd / || cd ..

pwd && ls
pwd || ls
pwd && pwd
pwd || pwd

pwd && ls && echo hi
pwd || ls && echo hi
pwd && ls || echo hi
pwd || ls || echo hi

ls || pwd
pwd || ls
ls && pwd
pwd && ls

env && echo $VAR
env || echo $VAR

exit && echo "This should not print"
exit || echo "This should not print"

ls || ;
; || ls
ls && ;
; & ls

ls || <
ls && <

(ls && pwd)
( (ls && pwd) )
( (ls) &&pwd)
(ls && ( ( pdw )))
(ls && pwd) > hi
(ls)
( ( ls ))
( (ls) )
ls && (ls)
(ls||pwd)&&(ls||pwd)
(ls&&pwd)&&(ls&&pwd)

```