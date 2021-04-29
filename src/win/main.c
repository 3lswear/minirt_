/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/29 15:02:09 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void     pixel_put(t_win *window, int x, int y, int color)
{
    char    *dst;

    dst = window->addr + (y * window->line_l + x * (window->bpp / 8));
    *(unsigned int *)dst = color;
}

int key_press_hook(int keycode, t_win *win)
{
	if (keycode == KEY_Q)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
		mlx_destroy_display(win->mlx);
		exit(0);
	}
	else
		return (0);
}
int idk_hook(int keycode, t_win *win)
{
	printf("keycode is => %d\n", keycode);
	(void)win;
	return (0);
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
	
	window.img = mlx_new_image(window.mlx, scene->width, scene->height);
	window.addr = mlx_get_data_addr(window.img, &window.bpp, &window.line_l, 
			&window.en);

	/* draw_circle(window, width, height); */


	iter_cams(scene, &window);
	/* trace(&window, scene); */
	//TODO: free scene

	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
	/* printf("strtof => %f\n", ft_strtof("0.14")); */
	printf("multiplied color is %X\n", c_mul(0x00101010, 0x00101010));
	printf("DONE!!\n");
	/* exit(1337); */
	mlx_hook(window.win, 2, 1L<<0, key_press_hook , &window);
	mlx_hook(window.win, 17, 1L<<24, idk_hook , &window);

    mlx_loop(window.mlx);
	return (0);
}      
