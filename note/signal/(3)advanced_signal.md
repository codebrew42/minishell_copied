# signal in minishell

##reference
https://velog.io/@jen133/minishell-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B2%98%EB%A6%AC

## signal

### types
- 1. ctrl c
	- print a new prompt
	- cat, grep으로 정지된 상태? print ^C -> disp new prompt
	- if err in buff? rm buff -> disp new prompt

2. ctrl \
	- do nothin
	- cat, grep으로 정지된 상태? print "^\QUIT : 3" -> term
3. ctrl D
	- exit shell
	- cat, grep으로 정지된 상태? term
	- err in buff? no behavior

### process


### termination
