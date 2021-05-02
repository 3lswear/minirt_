#include "minirt.h"

t_cylind	new_cylind(t_point *pos, t_vec *norm, double diam, double height)
{
	t_cylind	result;

	result.pos = pos;
	result.norm = norm;
	result.diam = diam;
	result.height = height;
	return (result);
}
