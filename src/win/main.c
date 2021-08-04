#include "minirt.h"

void	pixel_put(t_win *window, int x, int y, int color)
{
	char	*dst;

	dst = window->addr + (y * window->line_l + x * (window->bpp / 8));
	*(unsigned int *)dst = color;
}

int	check_save(int argc, char **argv)
{
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		{
			return (1);
		}
		else
		{
			handle_error(ERR_ARG, -1);
			return (0);
		}
	}
	else
		return (0);
}

char	*get_filename(char **argv, int argc)
{
	char	*filename;
	char	**split;
	int		sp_len;

	if (argc == 2 || argc == 3)
	{
		filename = argv[1];
		split = ft_split(filename, '.');
		sp_len = split_len(split);
		if (sp_len > 0 && !ft_strncmp("rt", split[sp_len - 1], 2))
		{
			liberator(split);
			return (filename);
		}
		else
		{
			handle_error(ERR_ARG, -1);
			return (NULL);
		}
	}
	else
	{
		handle_error(ERR_ARG, -1);
		return (NULL);
	}
}

int	main(int argc, char **argv)
{
	t_win	window;
	t_scene	*scene;
	int		save_bmp;
	char	*arg;

	arg = get_filename(argv, argc);
	save_bmp = check_save(argc, argv);
	parse_input(arg, &scene);
	window.mlx = mlx_init();
	iter_cams(scene, &window, save_bmp);
	return (0);
}
