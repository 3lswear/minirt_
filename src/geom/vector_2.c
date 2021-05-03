#include "minirt.h"

double	v_dot_product(t_vec *v1, t_vec *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

t_vec	*v_mult(t_vec *vec, double mult)
{
	t_vec	*result;

	result = v_new(vec->x * mult, vec->y * mult, vec->z * mult);
	return (result);
}

void	v_mult_inplace(t_vec *vec, double mult)
{
	vec->x *= mult;
	vec->y *= mult;
	vec->z *= mult;
}

int	v_equal(t_vec *v1, t_vec *v2)
{
	if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)
		return (1);
	else
		return (0);
}

t_vec	*v_cross(t_vec *a, t_vec *b)
{
	t_vec	*result;

	result = v_new(
			(a->y * b->z - a->z * b->y),
			(a->z * b->x - a->x * b->z),
			(a->x * b->y - a->y * b->x)
			);
	return (result);
}
