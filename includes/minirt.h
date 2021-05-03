/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:24:28 by sunderle          #+#    #+#             */
/*   Updated: 2021/05/03 13:05:20 by sunderle         ###   ########.fr       */
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

# define W_MAX 1920
# define H_MAX 1080

# define ERR_ALLOC	-1
# define ERR_LIST	-2
# define ERR_ARG	-3
# define ERR_SUBNORM -4
# define ERR_NEG	-5
# define ERR_FILE	-6

# define SHININESS	100

# define KEY_Q 113
# define KEY_ESC	0xFF1B
# define KEY_SPC	0x20

# define X_EVENT_KEY_PRESS 2

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
# include "objects.h"
# include "utils.h"
# include "rt.h"
# include "inter.h"
/* typedef int t_color; */

# define T_SPHERE 1
# define T_PLANE 2
# define T_SQUARE 3
# define T_TRIANG 4
# define T_CYLIND 5

/* typedef enum e_type {sphere, plane} t_type; */

void	pixel_put(t_win *window, int x, int y, int color);

#endif
