/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/05/03 13:42:29 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void     pixel_put(t_win *window, int x, int y, int color)
{
    char    *dst;

    dst = window->addr + (y * window->line_l + x * (window->bpp / 8));
    *(unsigned int *)dst = color;
}


void draw_circle(t_win window, int width, int height)
{
	int x;
	int y;

	x = -width / 2;
	while (x < width / 2)
	{
		y = -height / 2;
		while (y < height / 2)
		{
			if (pow(x, 2) + pow(y, 2) <= 22500)
				pixel_put(&window, x + width / 2, y + height / 2, BLUE);
			/* mlx_pixel_put(window.mlx, window.win, x, y, 0x000000FF); */
			y++;
		}
		x++;
	}
}

/* char *check_filename(char *name) */
/* { */
/* 	char **split; */
/* 	/1* split_len *1/ */
/* 	split = ft_split(name, '.'); */
/* 	if (1) */

/* } */

int check_save(int argc, char **argv)
{
	if (argc == 3) 
	{
		if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		{
			printf("OK GONNA SAVE NOW\n\n");
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

char *get_filename(char **argv, int argc)
{
	if (argc == 2 || argc == 3)
		return (argv[1]);
	else
	{
		handle_error(ERR_ARG, -1);
		return (NULL);
	}
}

int	main(int argc, char **argv)
{
	/* int offset; */
	t_win window;
	t_scene *scene;
	int	save_bmp;

	char *arg;
	arg = get_filename(argv, argc);
	save_bmp = check_save(argc, argv);

	parse_input(arg, &scene, &window);

    window.mlx = mlx_init();
	iter_cams(scene, &window, save_bmp);
	

	/* draw_circle(window, width, height); */


	/* trace(&window, scene); */
	//TODO: free scene

	/* printf("strtof => %f\n", ft_strtof("0.14")); */
	/* printf("multiplied color is %X\n", c_mul(0x00101010, 0x00101010)); */
	printf("DONE!!\n");
	/* exit(1337); */
	return (0);
}      
