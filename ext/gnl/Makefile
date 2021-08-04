NAME = gnltest

# CC = gcc
CC = clang

DECLARE_BUFSIZE = -D BUFFER_SIZE=35

CFLAGS = -Wall -Wextra -Werror 
CFLAGS += -g
LDFLAGS += -g



SRC = $(wildcard *.c)
	  # main.c\
	  # get_next_line.c\
	  # get_next_line.h\
	  # get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

HEADER = get_next_line.h

INCLUDES = ./

all: $(NAME)

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

GREPHL = grep  --color=always -e "^" -e "Error"


norm:
	@norminette $(filter-out main.c, $(SRC)) | $(GREPHL)
	@norminette $(HEADER) | $(GREPHL)

.PHONY: clean fclean all re
