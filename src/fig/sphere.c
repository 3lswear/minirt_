#include "minirt.h"

t_sphere *new_sphere(t_vec *center, float radius)
{
	t_sphere *result;
	
	result = malloc(sizeof(t_sphere));
	if (!result)
		handle_error(-1);
	result->center = center;
	result->radius = radius;
	return (result);

}
