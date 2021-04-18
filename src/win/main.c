/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/18 05:15:51 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void            pixel_put(t_win *win, int x, int y, int color)
{
    char    *dst;

    dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
    *(unsigned int *)dst = color;
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

	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);

    mlx_loop(window.mlx);
	return (0);
}      
