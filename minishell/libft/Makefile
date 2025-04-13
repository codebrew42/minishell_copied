# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ******** <********@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 15:41:33 by ********          #+#    #+#              #
#    Updated: 2025/03/15 21:59:56 by ********         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =  ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_issign.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_random.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c 
        #ft_printf.c \
        ft_check_conditions.c \
	ft_parse_str.c \
        ft_parse_format.c \
        ft_hub_printtype.c \
        ft_pf_int.c \
        ft_pf_uin.c \
        ft_pf_chr.c \
        ft_pf_ptr.c \
        ft_pf_hex.c \
        ft_pf_str.c \
        ft_put_intform.c \
        ft_put_hexform.c
OBJS = $(SRCS:.c=.o)
BONUS_S = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c
BONUS_O = $(BONUS_S:.c=.o)
CC = cc
INCLUDES = -Iinclude
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
VPATH = src printf

all: $(NAME)

$(NAME): $(OBJS)
	echo $(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	$(RM) $(OBJS) $(BONUS_O)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

bonus: $(OBJS) $(BONUS_O)
	ar -rc $(NAME) $(OBJS) $(BONUS_O)

debug: CFLAGS += -g
debug: fclean bonus

.PHONY:	all clean fclean re bonus
