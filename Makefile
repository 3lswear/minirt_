NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC = $(wildcard ./src/*c )

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes/

MLXFLAGS = -Lmlx-linux -lmlx -lXext -lX11

# MLX = ./mlx/libmlx.a
MLX = ./mlx-linux/libmlx.a

all: $(NAME)

$(OBJS): %.o %.c 
	$(CC) $(CFLAGS) -c $< -I ./mlx-linux  -I $(INCLUDES)-o $@

$(NAME): $(MLX) $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) -lm -o $(NAME)

$(MLX):
	cd mlx-linux
	sudo ./configure

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


run: $(NAME)
	./$(NAME)

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"
