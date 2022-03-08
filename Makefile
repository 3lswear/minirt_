NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = ./includes
HEADER = $(INCLUDES)/minirt.h
HEADERS = camera.h \
	color.h \
	geom.h \
	inter.h \
	list.h \
	minirt.h \
	objects.h \
	rt.h \
	scene.h \
	utils.h \
	win.h
SRC = src/fig/cylinder.c \
	src/fig/object.c \
	src/fig/plane.c \
	src/fig/sphere.c \
	src/fig/square.c \
	src/fig/triang.c \
	src/geom/lightsource.c \
	src/geom/vector.c \
	src/geom/vector_2.c \
	src/geom/vector_3.c \
	src/inter/calc_light.c \
	src/inter/calc_lights.c \
	src/inter/hit_funcs.c \
	src/inter/inter_cylind.c \
	src/inter/inter_cylind_help.c \
	src/inter/inter_objects.c \
	src/inter/inter_plane.c \
	src/inter/inter_sphere.c \
	src/inter/inter_square.c \
	src/inter/inter_triang.c \
	src/list/ft_lstadd_back.c \
	src/list/ft_lstadd_front.c \
	src/list/ft_lstclear.c \
	src/list/ft_lstdelone.c \
	src/list/ft_lstiter.c \
	src/list/ft_lstlast.c \
	src/list/ft_lstnew.c \
	src/list/ft_lstsize.c \
	src/parse/element_parsers.c \
	src/parse/object_parsers.c \
	src/parse/parse_cams.c \
	src/parse/parse_helpers.c \
	src/parse/parse_helpers_2.c \
	src/parse/parse_input.c \
	src/parse/parse_res.c \
	src/rt/iter_cams.c \
	src/rt/trace.c \
	src/scene/camera.c \
	src/scene/scene.c \
	src/utils/color.c \
	src/utils/divide.c \
	src/utils/free4.c \
	src/utils/freers.c \
	src/utils/ft_strtof.c \
	src/utils/graceful_exit.c \
	src/utils/handle_error.c \
	src/utils/misc.c \
	src/utils/screenshot.c \
	src/utils/split_len.c \
	src/utils/split_ws.c \
	src/utils/strchr_ws.c \
	src/win/main.c

OBJ = $(SRC:.c=.o)

GNL_HEADER = ./ext/gnl/get_next_line.h
GNL_SRC =	./ext/gnl/get_next_line.c ./ext/gnl/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

LIBFT_HEADER = ./ext/libft/libft.h
LIBFT = ./ext/libft/libft.a
LIBFT_FLAGS = -L=ext/libft -lft
LIBFT_SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memcpy_bd.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd. \
	ft_putendl_fd. \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strchr_bd.c \
	ft_strdup.c \
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

# MLX = ./mlx/libmlx.a
MLXFLAGS = -Lmlx-linux -lmlx -lXext -lX11
MLX = ./mlx-linux/libmlx.a

all: $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -I ./mlx-linux -I $(INCLUDES) -o $@

$(GNL_OBJ): %.o: %.c $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -include $(GNL_HEADER) -o $@

$(LIBFT):
	$(MAKE) -C ./ext/libft

$(MLX): $(wildcard ./mlx-linux/*.c)
	sudo make -C ./mlx-linux

$(NAME): $(LIBFT) $(GNL_OBJ) $(OBJ) $(MLX)
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
	./$(NAME) $(filter-out $@,$(MAKECMDGOALS))

test: $(NAME)
	./$(NAME) maps/test.rt

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"
	norminette $(GNL_HEADER) | grep "Error"
	norminette $(GNL_SRC) | grep "Error"
	norminette $(LIBFT_HEADER) | grep "Error"
	norminette $(LIBFT_SRC) | grep "Error"

