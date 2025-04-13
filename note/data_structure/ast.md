# ast data
```c
typedef enum e_token_type
{
	TK_INVALID,
	TK_WORD = 1,				// Regular text/command/args  including quotes
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_REDIR_IN,		// <
	TK_REDIR_OUT,		// >
	TK_REDIR_APP,		// >>
	TK_REDIR_HDC,		// <<
	TK_ENV_QUESTION,	// $?
	TK_ENV_VAR,			// $VAR
}   t_token_type;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}   t_ast;
```
---
## TK_WORD
only for cmd?

args: {"ls", "-l", NULL}

## TK_PIPE

args: NULL

## TK_OR

args: NULL

## TK_AND

args: NULL

## TK_REDIR_IN

args: "filename"

## TK_REDIR_OUT

args: "filename"

## TK_REDIR_APP

args: "filename"

## TK_REDIR_HDC

args: NULL

## TK_ENV_QUESTION

no use for excutor

## TK_ENV_VAR

no use for excutor
