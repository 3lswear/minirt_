#include "minirt.h"

t_hit inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere)
{
	float b;
	float c;
	float discr;
	/* float hit1; */
	/* float hit2; */
	t_vec *cam2sphere;
	t_hit hit;

	/* hit1 = 0; */
	/* hit2 = 0; */


	/* printf("sphere->radius = %f\n", sphere->radius); */
	cam2sphere = v_sub(origin, sphere->center);
	b = 2 * v_dot_product(cam2sphere, ray);
	c = v_dot_product(cam2sphere, cam2sphere) - (pow((sphere->diam / 2.0), 2));
	discr = (b * b) - (4 * c);
	free(cam2sphere);
	if (discr < 0)
	{
		hit.a = 0;
		hit.b = 0;
		return (hit);
	}
	hit.a = (-b - sqrt(discr)) / 2;
	hit.b = (-b + sqrt(discr)) / 2;
	return (hit);
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
	/* 	/1* if (hit1 > 0) *1/ */
	/* 	/1* 	return (hit1); *1/ */
	/* 	/1* else *1/ */
	/* 	/1* 	return (hit2); *1/ */
	/* 	if (hit1 > hit2) */
	/* 		return (hit1); */
	/* 	else */
	/* 		return (hit2); */
	/* } */
	/* else */
	/* 	return (0); */

	/* /1* if both positive then return smaller one *1/ */
	/* if ((hit1 * hit2 > 0) && hit1 > FLT_EPSILON) */
	/* { */
	/* 	if (hit1 > hit2) */
	/* 		return (hit2); */
	/* 	else */ 
	/* 		return (hit1); */
	/* } */
	/* else if ((hit1 * hit2) < 0) */
	/* { */
	/* 	if (hit1 > hit2) */
	/* 		return (hit1); */
	/* 	else */ 
	/* 		return (hit2); */
	/* } */
	/* /1* else if (hit1 > FLT_EPSILON) *1/ */
	/* /1* 	return (hit1); *1/ */
	/* /1* else if (hit2 > FLT_EPSILON) *1/ */
	/* /1* 	return (hit2); *1/ */
	/* else */
	/* 	return (0); */
}
