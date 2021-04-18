#include "minirt.h"

t_vector *new_vec(float x, float y, float z)
{
	t_vector *vec;

	vec = malloc(sizeof(t_vector));
	/* if (!vec) */
	/* 	error(-1); */
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}
