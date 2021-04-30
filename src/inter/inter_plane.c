#include "minirt.h"

double inter_plane(t_vec *origin, t_vec *ray, t_plane *plane)
{
	/* double ray_len; */
	double t;
	t_vec *tmp;

	/* ray_len = 0; */
	/* (void)origin; */
	/* if ((n->x * (ray->x - m->x) + */
	/* 		n->y * (ray->y - m->y) + */
	/* 		n->z * (ray->z - m->z)) == 0) */
	/* 	return () */
	tmp = v_sub(plane->pos, origin);

	t = (v_dot_product(tmp, plane->norm))
			/ (v_dot_product(ray, plane->norm));
	free(tmp);
	/* ray_len = v_mult(ray, t); */
	/* ray_len = t; */
	/* printf("len to plane => %f\n", t); */
	/* if (t > 0) */
	/* { */
	/* 	return (t); */
	/* } */
	/* else */
	/* 	return (0); */
	return (t);
}

/* t_color calc_light_matte_plane(t_plane *sphere, t_light *light, t_vec *ray, double ray_len) */
/* { */
/* 	t_point *surface_point; */
/* 	t_vec *n; */
/* 	t_vec *l; */
/* 	double strength; */


/* 	surface_point = v_mult(ray, ray_len); */
/* 	l = v_sub(light->coords, surface_point); */
/* 	n = v_sub(surface_point, sphere->center); */
/* 	v_norm_inplace(n); */
/* 	/1* printf("surface_point\t-> %f,%f,%f\n", surface_point->x, surface_point->y, surface_point->z); *1/ */
/* 	/1* printf("light_point\t-> %f,%f,%f\n", l_norm->x, l_norm->y, l_norm->z); *1/ */
/* 	strength = v_dot_product(n, l) / (v_len(l) * v_len(n)); */
/* 	/1* printf("strength => %f\n", strength); *1/ */
/* 	/1* printf("color =>%X\n", color); *1/ */
/* 	free(surface_point); */
/* 	if (v_dot_product(n, l) > 0) */
/* 	{ */
/* 		free(l); */
/* 		free(n); */
/* 		return(c_mul_scalar(light->color, (light->brightess * strength))); */
/* 	} */
/* 	else */
/* 	{ */
/* 		free(l); */
/* 		free(n); */
/* 		return (0); */
/* 	} */
/* } */
