#include "minirt.h"

double inter_square(t_point *origin, t_vec *ray, t_square *square)
{
	/* double ray_len; */
	t_plane plane;
	t_vec *u;
	t_vec *w;
	t_point *a;
	t_point *b;
	t_point *c;
	t_point *d;

	double hside;

	t_triang t1;
	t_triang t2;

	t_hit hit;

	plane.color = BLACK;
	hside = square->side / 2;
	plane.norm = square->norm;
	plane.pos = square->pos;
	/* ray_len = inter_plane(origin, ray, &plane); */
	u = v_cross(square->norm, v_new(0,1,0));
	if (v_len(u) < FLT_EPSILON)
	{
		u = v_cross(square->norm, v_new(1,0,0));
	}
	/* print_vec(u, "u is: "); */
	v_norm_inplace(u);
	w = v_cross(square->norm, u);
	v_norm_inplace(w);

	a = v_add(v_add(v_mult(u, hside), v_mult(w, hside)), square->pos);
	b = v_add(v_sub(v_mult(u, hside), v_mult(w, hside)), square->pos);
	c = v_sub(square->pos, v_add(v_mult(u, hside), v_mult(w, hside)));
	d = v_sub(square->pos, v_sub(v_mult(u, hside), v_mult(w, hside)));
	/* print_vec(a, "a pos "); */
	/* print_vec(b, "b pos "); */
	/* print_vec(c, "c pos "); */
	/* print_vec(d, "d pos "); */

	t1 = new_triang(a, b, c, square->color);
	t2 = new_triang(a, c, d, square->color);

	t1.norm = triang_get_norm(&t1);
	t2.norm = triang_get_norm(&t2);
	
	hit.a = inter_triang(origin, ray, &t1);
	hit.b = inter_triang(origin, ray, &t2);

	if (hit.a > 0)
		return (hit.a);
	else 
		return (hit.b);

	/* if (ray_len < 0) */
	/* 	return (ray_len); */
	/* return (0); */

}
