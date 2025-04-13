## tester
1. only pwd
2. with cd

```shell
pwd
cd .. && pwd
cd ../.. && pwd
cd ../../.. && pwd
cd / && pwd
cd $HOME && pwd
pwd | cat -e
PWD=/etc && pwd
unset PWD; pwd; echo $PWD
export PWD=foo; pwd; echo $PWD
Pwd
pwD
Pwd
pwD

```