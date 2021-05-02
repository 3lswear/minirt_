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
	t_vec	up;

	up = v_new_s(0, 1, 0);
	u = v_cross(square->norm, &up);
	if (v_len(u) < FLT_EPSILON)
	{
		up = v_new_s(1, 0, 0);
		u = v_cross(square->norm, &up);
	}
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
	free4(u, w, u_plus_w, u_min_w);
}
