#include "minirt.h"

t_hit inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere)
{
	double b;
	double c;
	double discr;
	t_vec *cam2sphere;
	t_hit hit;

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
}
