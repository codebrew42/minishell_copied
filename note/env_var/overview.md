
## environment variables should work in minishell
- $ : variable
- \$$ : pid of the shell
- $? : last exit status
- $* : all arguments
- $# : number of arguments

## how it looks like
- check
```bash
echo $HOME
echo $$
echo $?
echo $*
echo $#
```

## exaple
```bash
export NAME=value
echo $NAME
```