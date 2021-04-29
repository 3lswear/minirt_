#include "minirt.h"

t_vec	*v_new(double x, double y, double z)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		handle_error(-1);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec	*v_sub(t_vec *v1, t_vec *v2)
{
	t_vec	*result;

	result = v_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (result);
}

double	v_len(t_vec *vec)
{
	double	result;

	result = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (result);
}

void	v_norm(t_vec	*vec)
{
	double	len;

	len = v_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

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
