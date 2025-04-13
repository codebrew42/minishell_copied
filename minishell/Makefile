# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ******** <********@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 16:26:53 by ********          #+#    #+#              #
#    Updated: 2025/04/02 17:13:04 by ********         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRCS	=	init.c \
		main.c \
		err_handler.c \
		tokenizer.c \
		handle_operator.c \
		handle_word.c \
		valid_tk.c \
		free_ms.c \
		parser.c \
		validate_single_op.c \
		validate_linked_op.c \
		util_cmd_with_redir.c \
		util_type_check.c \
		util_save_to_ast.c \
		print_debug.c \
		heredoc.c \
		heredoc_init.c \
		heredoc_utils.c \
		free_ms_utils.c \
		envvar_expander.c \
		ev_expander_utils.c \
		wc_expander.c \
		wc_expander_utils.c \
		executor.c \
		exec_init.c \
		exec_cmdproc.c \
		exec_stream.c \
		exec_builtin.c \
		exec_utils.c \
		exec_utils2.c \
		ms_pwd.c \
		ms_cd.c \
		ms_echo.c \
		ms_env.c \
		ms_export.c \
		ms_unset.c \
		ms_exit.c \
		builtin_utils.c \
		builtin_utils2.c \
		signal.c \
		signal_util.c \
		handle_qot_envvar.c \
		util_check_qot.c \
		test_utils.c \
		test_utils2.c 
OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
INCLUDES = -Iinclude -Ilibft/include
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -Llibft -lft -lreadline
LIBFT_MAKE = make bonus
VPATH = src src/init src/err src/signal src/tokenizer src/ms_free src/parser \
	src/heredoc src/ms_free src/executor src/expander src/builtins src/test

# Detect OS=> macOS specific flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # Check if Homebrew is installed in /opt/homebrew (Apple Silicon) or /usr/local (Intel)
    ifeq ($(shell test -d /opt/homebrew && echo yes),yes)
        LDFLAGS = -L/opt/homebrew/opt/readline/lib
        CPPFLAGS = -I/opt/homebrew/opt/readline/include
    else
        LDFLAGS = -L/usr/local/opt/readline/lib
        CPPFLAGS = -I/usr/local/opt/readline/include
    endif
endif

all: $(NAME)

$(NAME): obj $(OBJS)
	$(LIBFT_MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

obj:
	mkdir -p obj

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -rf obj

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: LIBFT_MAKE = make debug
debug: fclean all

#valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re debug
