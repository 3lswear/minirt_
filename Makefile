NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC = $(wildcard ./src/*/*c )

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes

HEADER = $(INCLUDES)/minirt.h

MLXFLAGS = -Lmlx-linux -lmlx -lXext -lX11

GNL_SRC =	./ext/gnl/get_next_line.c ./ext/gnl/get_next_line_utils.c

GNL_OBJ = $(GNL_SRC:.c=.o)

GNL_HEADER = ./ext/gnl/get_next_line.h

# MLX = ./mlx/libmlx.a
MLX = ./mlx-linux/libmlx.a

all: $(NAME)

$(GNL_OBJ): %.o: %.c $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -include $(GNL_HEADER) -o $@

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I ./mlx-linux -I $(INCLUDES) -o $@

$(MLX):
	cd mlx-linux
	sudo ./configure

$(NAME): $(OBJ) $(GNL_OBJ) $(MLX) 
	$(CC) $(OBJ) $(GNL_OBJ) $(MLXFLAGS) -lm -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(GNL_OBJ)

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
