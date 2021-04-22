#include "minirt.h"

t_vec *v_new(float x, float y, float z)
{
	t_vec *vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		handle_error(-1);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec *v_sub(t_vec *v1, t_vec *v2)
{
	t_vec *result;

	result = v_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (result);
}

float v_len(t_vec *vec)
{
	float result;

	result = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (result);
}

void v_norm(t_vec *vec)
{
	float len;

	len = v_len(vec);

	vec->x /= len;
	vec->y /= len;
	vec->z /= len;

}

float v_dot_product(t_vec *v1, t_vec *v2)
{
	float result;

	result = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (result);
}

t_vec *v_mult(t_vec *vec, float mult)
{
	t_vec *result;
	result = v_new(vec->x * mult, vec->y * mult, vec->z * mult);
	return (result);
}

int v_equal(t_vec *v1, t_vec *v2)
{
	if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)
		return (1);
	else
		return (0);
}



