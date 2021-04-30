#include "minirt.h"

t_sphere	new_sphere(t_vec *center, double diam)
{
	t_sphere	result;

	result.center = center;
	result.diam = diam;
	return (result);
}
