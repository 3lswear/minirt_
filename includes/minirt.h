/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:24:28 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:37:18 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000

#include "../mlx-linux/mlx.h"
#include "../ext/gnl/get_next_line.h"
#include "../ext/libft/libft.h"
     #include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "geom.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"
#include "utils.h"
#include "rt.h"
#include "inter.h"

typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_win;

#define RAD (M_PI / 180)


void	pixel_put(t_win *window, int x, int y, int color);
void	trace(t_win *window, t_scene *scene);

#endif
