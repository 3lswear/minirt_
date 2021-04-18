NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC = $(wildcard ./src/*/*c )

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes

HEADER = $(INCLUDES)/minirt.h

MLXFLAGS = -Lmlx-linux -lmlx -lXext -lX11

# MLX = ./mlx/libmlx.a
MLX = ./mlx-linux/libmlx.a

all: $(NAME)

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I ./mlx-linux -I $(INCLUDES) -o $@

$(MLX):
	cd mlx-linux
	sudo ./configure

$(NAME): $(OBJ) $(MLX) 
	$(CC) $(OBJ) $(MLXFLAGS) -lm -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"
