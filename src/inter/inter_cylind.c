#include "minirt.h"

t_hit	inter_cylind(t_point *origin, t_vec *ray, t_cylind *cy)
{
	t_hit hit;
	double rad;
	double discr;
	double a;
	double b;
	double c;
	t_vec *cam2cent;
	/* t_point *cap1point; */
	double m1;
	/* double m2; */

	/* cap1point = v_add(cy->pos, v_mult(cy->norm, cy->height / 2)); */
	/* print_vec(cap1point, "cap1point"); */
	/* printf("%lf\n", v_dot_product(v_sub(cap1point, origin), cy->norm)); */
	/* print_vec(v_sub(cap1point, origin), "cam2cap1"); */
	/* if (v_dot_product(ray, v_add(cy->norm, cy->pos)) > 0) */
	/* { */
	/* 	hit.a = 0; */
	/* 	hit.b = 0; */
	/* 	return (hit); */
	/* } */
	rad = cy->diam / 2.0;
	/* cam2cent = v_sub(origin, cy->pos); */
	cam2cent = v_sub(origin, v_add((cy->pos), v_mult(cy->norm, cy->height / 2)));
	a = v_dot_product(ray, ray) - pow(v_dot_product(ray, cy->norm), 2);
	b = v_dot_product(ray, cam2cent) - v_dot_product(ray, cy->norm) *
		v_dot_product(cam2cent, cy->norm);
	c = v_dot_product(cam2cent, cam2cent) - pow(v_dot_product(cam2cent, cy->norm), 2) 
		- pow(rad, 2);
	b = b * 2.0;
	discr = (b * b) - (4 * a * c);
	if (discr < 0)
	{
		hit.a = 0;
		hit.b = 0;
		return (hit);
	}
	hit.a = (-b - sqrt(discr)) / (2 * a);
	hit.b = (-b + sqrt(discr)) / (2 * a);
	
	if (hit.a * hit.b > 0)
	{
		m1 = v_dot_product(ray, v_mult(cy->norm, get_positive(hit))) + v_dot_product(cam2cent, cy->norm);
		/* m1 = v_dot_product(v_add(v_mult(ray, get_positive(hit)), cam2cent), ray); */
		/* m2 = v_dot_product(v_add(v_mult(ray, hit.b), cam2cent), ray); */
		printf("m1 => %lf\n", m1);
		/* printf("m2 => %lf\n", m2); */
		/* if ((m1 <= 1 && m1 >= 0) || (m2 <= 1 && m2 >= 0)) */
		if (m1 < cy->height / 2 && m1 > -(cy->height / 2))
			return(hit);
	}
	hit.a = 0;
	hit.b = 0;
	return (hit);
}
