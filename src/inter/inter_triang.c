#include "minirt.h"

float	inter_triang(t_point *origin, t_vec *ray, t_triang *tri)
{
	t_vec *edge1;
	t_vec *edge2;
	t_vec *h;
	t_vec *s;
	t_vec *q;
	float a;
	float f;
	float u;
	float v;
	float t;

	edge1 = v_sub(tri->b, tri->a);
	edge2 = v_sub(tri->c, tri->a);
	h = v_cross(ray, edge2);
	a = v_dot_product(edge1, h);
	if (a > -FLT_EPSILON && a < FLT_EPSILON)
		return (0);
	f = 1.0 / a;
	s = v_sub(origin, tri->a);
	u = f * v_dot_product(s, h);
	if (u < 0.0 || u > 1.0)
		return (0);
	q = v_cross(s, edge1);
	v = f * v_dot_product(ray, q);
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = f * v_dot_product(edge2, q);
	if (t > FLT_EPSILON)
		return (v_dot_product(edge2, q) * f);
	return (0);
}
