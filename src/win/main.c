/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/20 02:42:34 by sunderle         ###   ########.fr       */
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

int	main(void)
{
	int width;
	int height;
	/* int offset; */

	width = 1366;
	height = 768;

	t_win window;

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, width, height, "jopa");
	
	window.img = mlx_new_image(window.mlx, width, height);
	window.addr = mlx_get_data_addr(window.img, &window.bpp, &window.line_l, 
			&window.en);

	/* draw_circle(window, width, height); */
	t_sphere *sph;
	t_vec *sph_center;

	t_cam *cam;
	t_vec *cam_dir;
	t_vec *cam_origin;
	float cam_fov;

	t_scene *scene;

	sph_center = v_new(3, 2, -20);
	sph = new_sphere(sph_center, 4);

	cam_dir = v_new(0, 0, -1);
	cam_origin = v_new(0, 0, 0);
	cam_fov = 90;
	cam = new_cam(cam_origin, cam_dir, cam_fov);

	scene = new_scene(cam, sph);
	scene->width = width;
	scene->height = height;

	trace(&window, scene);
	//TODO: free scene
	parse_input("maps/test.rt", scene);
	/* ft_putstr_fd("JOPA TEst!!!!", 1); */

	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
	mlx_hook(window.win, 2, 1L<<0, win_close , &window);

    mlx_loop(window.mlx);
	return (0);
}      
