#include "minirt.h"


float inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere)
{
	float b;
	float c;
	float discr;
	float hit1;
	float hit2;
	t_vec *cam2sphere;

	hit1 = 0;
	hit2 = 0;

	/* printf("sphere->radius = %f\n", sphere->radius); */
	cam2sphere = v_sub(origin, sphere->center);
	b = 2 * v_dot_product(cam2sphere, ray);
	c = v_dot_product(cam2sphere, cam2sphere) - (pow((sphere->diam / 2), 2));
	discr = (b * b) - (4 * c);
	free(cam2sphere);
	if (discr < 0)
		return (0);
	hit1 = (-b - sqrt(discr)) / 2;
	hit2 = (-b + sqrt(discr)) / 2;
	//choose which distance to return
	/* if ((hit1 * hit2) > 0) */
	/* ОПТИМИЗИРОВАТЬ */
	/* if (hit1 > 0 && hit2 > 0) */
	/* { */
	/* 	if (hit1 > hit2) */
	/* 		return (hit2); */
	/* 	else */
	/* 		return (hit1); */
	/* } */
	/* else if ((hit1 * hit2) < 0) */
	/* { */
	/* 	if (hit1 > 0) */
	/* 		return (hit1); */
	/* 	else */
	/* 		return (hit2); */
	/* } */
	/* else */
	/* 	return (0); */
	if (hit1 > hit2)
		return (hit2);
	else 
		return (hit1);
}
