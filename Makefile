NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = ./includes

HEADER = $(INCLUDES)/minirt.h
SRC = $(wildcard ./src/*/*c )
OBJ = $(SRC:.c=.o)

GNL_HEADER = ./ext/gnl/get_next_line.h
GNL_SRC =	./ext/gnl/get_next_line.c ./ext/gnl/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

LIBFT_HEADER = ./ext/libft/libft.h
LIBFT = ./ext/libft/libft.a
LIBFT_FLAGS = -L=ext/libft -lft

# MLX = ./mlx/libmlx.a
MLXFLAGS = -Lmlx-linux -lmlx -lXext -lX11
MLX = ./mlx-linux/libmlx.a

all: $(NAME)

$(GNL_OBJ): %.o: %.c $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -include $(GNL_HEADER) -o $@

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I ./mlx-linux -I $(INCLUDES) -o $@

$(MLX):
	cd mlx-linux
	sudo ./configure

$(LIBFT):
	$(MAKE) -C ./ext/libft

$(NAME): $(OBJ) $(GNL_OBJ) $(MLX) $(LIBFT)
	$(CC) $(OBJ) $(GNL_OBJ) $(MLXFLAGS) $(LIBFT_FLAGS) -lm -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(GNL_OBJ)
	$(MAKE) clean -C ./ext/libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./ext/libft

re:
	$(MAKE) fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"
