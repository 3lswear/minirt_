#include "minirt.h"

t_triang	new_triang(t_point *a, t_point *b, t_point *c, t_color color)
{
	t_triang	result;

	result.a = a;
	result.b = b;
	result.c = c;
	result.color = color;
	return (result);
}

t_vec	*triang_get_norm(t_triang *tri)
{
	t_vec	*edge1;
	t_vec	*edge2;
	t_vec	*norm;

	edge1 = v_sub(tri->b, tri->a);
	edge2 = v_sub(tri->c, tri->a);
	tri->edge1 = edge1;
	tri->edge2 = edge2;
	norm = v_cross(edge1, edge2);
	v_norm_inplace(norm);
	return (norm);
}
