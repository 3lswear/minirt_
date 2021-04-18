/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:24:28 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/18 23:55:53 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000

     #include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../mlx-linux/mlx.h"
#include "vector.h"
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

/* PROTOTYPES */

void handle_error(int value);

void     pixel_put(t_win *window, int x, int y, int color);
void trace(t_win *window, t_scene *scene);

/* GEOMETRY */


t_vec *new_vec(float x, float y, float z);
t_vec *v_sub(t_vec *v1, t_vec *v2);
float v_len(t_vec *vec);
void v_norm(t_vec *v);
float v_dot_product(t_vec *v1, t_vec *v2);

#endif
