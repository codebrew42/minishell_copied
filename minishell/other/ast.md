## ast

---

```c
typedef enum e_token_type
{
	TK_INVALID,
	TK_WORD = 1,				//TK:  Regular text/command/args  including quotes
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_REDIR_IN,		// < : ARGS: NULL
	TK_REDIR_OUT,		// >
	TK_REDIR_APP,		// >>
	TK_REDIR_HDC,		// <<
	TK_DOLLAR,			// $  (only for $?, $VAR)   
	TK_ENV_QUESTION,	// ?
	TK_ENV_VAR,			//PATH
}   t_token_type;



typedef struct s_ast
{
	t_token_type	type;
	char			**args;		// Command + arguments (for executables) : (ls -l | wc -l) -> args[0] = ls, args[1] = -l, args[2] = wc, args[3] = -l
	struct s_ast	*left;		// Left child (e.g., input source)
	struct s_ast	*right;		// Right child (e.g., next command in pipe)
}   t_ast;


typedef struct s_mshell
{
	t_token		*tokens;
	t_ast		*ast_root;			// Root of the AST
	t_env		*env_var;
	char		**envp;				// Environment as char** for execve
	char		**path;
	int			hdc_flag;			
	int			exit_requested;		// check: Flag for exit command
	int			dollar_exit_status;		//for $?
}   t_mshell;

```

---

## AST

```c
ls -l

ast
{
	type = TYPE_CMD;
	args = {"ls", "-l", NULL};
}
```

```c
< file cat

ast
{
	type = TYPE_RED_IN, arg = file	
}
->next
ast
{
	type = TYPE_CMD;
	args = {"cat", NULL};
}


```



```


## process of tk & ps

### tokenizer
- saves type : or, and, red_in/out/here, env_question, env_var (no need to save 'dollar')
- validate : check error (just related to |  & $ < >)
		e.g. |||, &&&&

- examples

			< 		file		cat		|		wc		-l			"....'..'..."
TYPE		RED		WORD		WORD	PIPE	WORD	WORD		WORD
VALUE		NULL	"file"		"cat"	NULL	"wc"	"-l"		"....'..'..."

- check validaty of quotes : if balanced (means, outer quotes closed)

### parser

- divide word to CMD, FILE, TEXT

- sequence matters
	1) RED_IN, saves arg left
	2) RED_OUT, saves arg right
	3) pipe, or, and : doesn't save arg
	4) ENV_VAR, ENV_QUESTION : expanded here
	5) CMD, saves arg in a sequence

	**check syntax err(?) what and how?

	>> how "AST" looks like [1]
		e.g.	cd		dir		-r				||		=> echo		"hi friend'
		type	CMD								OR			CMD
		ARG		{"cd", "dir", "-r", NULL}		NULL		{"echo", "hi friend", NULL}

	>> how "AST" looks like [2]
		e.g.	>		file.txt		cat
		type	RED						CMD
		ARG		file.txt				'cat', NULL

	>> [3]
			cat			<		input.txt		|		grep		"pattern"		>		output.txt
	TYPE	CMD			RED_OUT					PIPE	cmd						RED_OUT
	ARG		"cat",NULL	input.txt				NULL	"grep","pattern",NUL	"output.txt"

	>> [4]
			cat					<<		EOF (delimiter)
	TYPE	CMD				RED_HRD
	ARG		"cat",NULL			EOF

			cat		<<		finish (delimiter)
	TYPE	CMD		RED_HRD
	ARG				"finish"


	>> [6]
			echo		hi			>>		file.txt
	TYPE	CMD						RED_APD	
	ARG		"echo", "hi", NULL		"file.txt", NULL


	>> [7] maybe syntax err
			echo		hi			>>		file1.txt		Str2
	TYPE	CMD						RED_APD	
	ARG		"echo", "hi", NULL		"file.txt", "str2", NULL

```c


```


### expander
- depends on the quotation

$ENV_VAR

	PATH -> real path 