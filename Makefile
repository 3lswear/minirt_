NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC = $(wildcard ./src/*c )

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes/

MLX = ./mlx/libmlx.a

all: $(NAME)

$(OBJS): %.o %.c 
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
