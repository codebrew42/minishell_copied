
## test: init.c
//dir: minishell
cc -Wall -Wextra -Werror -I./include -I./libft/src \
src/err_jin/print_err.c \
src/init/init.c \
libft/src/ft_strlen.c \
libft/src/ft_split.c \
libft/src/ft_strchr.c \
libft/src/ft_strdup.c \
libft/src/ft_strncmp.c \
libft/src/ft_substr.c \
libft/src/ft_putstr_fd.c \
libft/src/ft_memmove.c -o init

##save result
./init 10 > src/init/result.txt   