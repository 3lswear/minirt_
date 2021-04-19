# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunderle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 20:03:30 by sunderle          #+#    #+#              #
#    Updated: 2021/04/19 18:36:22 by sunderle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC = \
	./ft_atoi.c \
	./ft_isalpha.c \
	./ft_isprint.c \
	./ft_memcpy_bd.c \
	./ft_memset.c \
	./ft_strchr.c \
	./ft_strnstr.c \
	./ft_toupper.c\
	./ft_bzero.c \
	./ft_isascii.c \
	./ft_memchr.c \
	./ft_memcpy.c \
	./ft_strlen.c \
	./ft_strrchr.c\
	./ft_isalnum.c \
	./ft_isdigit.c \
	./ft_memcmp.c \
	./ft_memmove.c \
	./ft_strchr_bd.c \
	./ft_strncmp.c \
	./ft_tolower.c \
	./ft_strlcpy.c \
	./ft_strlcat.c \
	./ft_strdup.c \
	./ft_calloc.c \
	./ft_putstr_fd.c \
	./ft_putchar_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c \
	./ft_substr.c \
	./ft_strjoin.c \
	./ft_strtrim.c \
	./ft_itoa.c \
	./ft_strmapi.c \
	./ft_split.c \
	./ft_memccpy.c \

OBJS = $(SRC:.c=.o)

HEADER = libft.h

INCLUDES = ./

all: $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

# ADDITIONAL RULES!!!!
BSDFLAGS = -l=bsd
GREPHL = grep  --color=always -e "^" -e "Error"

main: $(NAME)
	$(RM) libft.so
	$(CC) $(CFLAGS) main.c $(BSDFLAGS) -L=. -l=ft && ./a.out

leak.out: $(NAME) leak.c
	$(RM) libft.so
	$(CC) $(CFLAGS) leak.c $(BSDFLAGS) -L=. -l=ft -o leak.out

leak: leak.out
	./leak.out

testleaks: leak.out
	valgrind ./leak.out

norm:
	norminette $(SRC) | $(GREPHL)
	norminette $(HEADER) | $(GREPHL)

so:
	$(CC) -fPIC $(CFLAGS) -c $(SRC)
	$(CC) -shared -o libft.so $(OBJS)

.PHONY: clean fclean all re
