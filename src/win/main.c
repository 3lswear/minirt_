/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/05/02 11:39:56 by sunderle         ###   ########.fr       */
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

char *parse_args(int argc, char **argv)
{
	if (argc == 2)
		return(argv[1]);
	else
	{
		handle_error(ERR_ARG);
		return (NULL);
	}
}

int	main(int argc, char **argv)
{
	/* int offset; */
	t_win window;
	t_scene *scene;

	char *arg;
	arg = parse_args(argc, argv);

	parse_input(arg, &scene, &window);

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, scene->width, scene->height, "🤠🤠🤠");
	

	/* draw_circle(window, width, height); */


	iter_cams(scene, &window);
	/* trace(&window, scene); */
	//TODO: free scene

	/* printf("strtof => %f\n", ft_strtof("0.14")); */
	/* printf("multiplied color is %X\n", c_mul(0x00101010, 0x00101010)); */
	printf("DONE!!\n");
	/* exit(1337); */
	return (0);
}      
