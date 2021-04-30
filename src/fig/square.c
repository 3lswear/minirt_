#include "minirt.h"

t_square	new_square(t_point *pos, t_vec *norm, double side, t_color color)
{
	t_square	result;

	result.pos = pos;
	result.norm = norm;
	result.side = side;
	result.color = color;
	return (result);
}

void	sq_get_vertices(t_square *square)
{
	t_vec	*u;
	t_vec	*w;
	t_vec	*u_plus_w;
	t_vec	*u_min_w;

	square->hside = square->side / 2.0;
	u = v_cross(square->norm, v_new(0, 1, 0));
	if (v_len(u) < FLT_EPSILON)
		u = v_cross(square->norm, v_new(1, 0, 0));
	v_norm_inplace(u);
	w = v_cross(square->norm, u);
	v_norm_inplace(w);
	v_mult_inplace(u, square->hside);
	v_mult_inplace(w, square->hside);
	u_plus_w = v_add(u, w);
	u_min_w = v_sub(u, w);
	square->a = v_add(u_plus_w, square->pos);
	square->b = v_add(u_min_w, square->pos);
	square->c = v_sub(square->pos, u_plus_w);
	square->d = v_sub(square->pos, u_min_w);
	free(u);
	free(w);
	free(u_plus_w);
	free(u_min_w);
}
