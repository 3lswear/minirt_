#include "minirt.h"

void	v_add_inplace(t_vec *a, t_vec *b)
{
	a->x = a->x + b->x;
	a->y = a->y + b->y;
	a->z = a->z + b->z;
}

double	v_len(t_vec *vec)
{
	double	result;

	result = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (result);
}

t_vec	*v_norm(t_vec *vec)
{
	t_vec	*result;
	double	len;

	len = v_len(vec);
	result = v_new(
			vec->x / len,
			vec->y / len,
			vec->z / len
			);
	return (result);
}

void	v_norm_inplace(t_vec	*vec)
{
	double	len;

	len = v_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}
