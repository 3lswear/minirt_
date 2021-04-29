#include "minirt.h"

t_sphere new_sphere(t_vec *center, double diam)
{
	t_sphere result;
	
	/* result = malloc(sizeof(t_sphere)); */
	/* if (!result) */
	/* 	handle_error(-1); */
	result.center = center;
	result.diam = diam;
	return (result);

}
