/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:24:28 by sunderle          #+#    #+#             */
/*   Updated: 2021/05/03 02:03:14 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define R_MASK	0x00FF0000
# define G_MASK	0x0000FF00
# define B_MASK	0x000000FF

# define WHITE	0x00FFFFFF
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define BLACK	0x00000000

# define ERR_ALLOC	-1
# define ERR_LIST	-2
# define ERR_ARG	-3
# define ERR_SUBNORM -4
# define ERR_NEG	-5

# define SHININESS	100

# define KEY_Q 113
# define KEY_ESC	0xFF1B
# define KEY_SPC	0x20

# include "../mlx-linux/mlx.h"
# include "../ext/gnl/get_next_line.h"
# include "../ext/libft/libft.h"
# include <stdio.h>
# include "float.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "win.h"
# include "color.h"
# include "list.h"
# include "geom.h"
# include "camera.h"
# include "scene.h"
# include "utils.h"
# include "objects.h"
# include "rt.h"
# include "inter.h"
/* typedef int t_color; */

# define T_SPHERE 1
# define T_PLANE 2
# define T_SQUARE 3
# define T_TRIANG 4
# define T_CYLIND 5

/* typedef enum e_type {sphere, plane} t_type; */

typedef union u_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_square	square;
	t_triang	triang;
	t_cylind	cylind;
}	t_object;

typedef struct s_obj
{
	int			type;
	t_color		color;
	t_object	obj;

}	t_obj;

void	pixel_put(t_win *window, int x, int y, int color);

#endif
