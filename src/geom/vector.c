#include "minirt.h"

t_vec	*v_new(double x, double y, double z)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		handle_error(-1, -1);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec	v_new_s(double x, double y, double z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec	*v_sub(t_vec *v1, t_vec *v2)
{
	t_vec	*result;

	result = v_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (result);
}

void	v_sub_inplace(t_vec *a, t_vec *b)
{
	a->x = a->x - b->x;
	a->y = a->y - b->y;
	a->z = a->z - b->z;
}

t_vec	*v_add(t_vec *a, t_vec *b)
{
	t_vec	*result;

	result = v_new(a->x + b->x, a->y + b->y, a->z + b->z);
	return (result);
}
