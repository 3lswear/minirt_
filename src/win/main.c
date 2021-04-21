/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/20 17:51:19 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void     pixel_put(t_win *window, int x, int y, int color)
{
    char    *dst;

    dst = window->addr + (y * window->line_l + x * (window->bpp / 8));
    *(unsigned int *)dst = color;
}

int win_close(int keycode, t_win *win)
{
	(void)keycode;
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
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
    window.win = mlx_new_window(window.mlx, scene->width, scene->height, "jopa");
	
	window.img = mlx_new_image(window.mlx, scene->width, scene->height);
	window.addr = mlx_get_data_addr(window.img, &window.bpp, &window.line_l, 
			&window.en);

	/* draw_circle(window, width, height); */


	trace(&window, scene);
	//TODO: free scene

	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
	mlx_hook(window.win, 2, 1L<<0, win_close , &window);

    mlx_loop(window.mlx);
	return (0);
}      
