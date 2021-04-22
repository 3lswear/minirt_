#include "minirt.h"

int argb_color(unsigned char r, unsigned char g, unsigned char b)
{
	int color;
	color = 0;
	color += r;
	color = color << 8;
	color += g;
	color = color << 8;
	color+= b;
	/* printf("color is %X\n", color); */
	return (color);

}

int inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	int color;
	t_list *current;

	color = -1;
	current = scene->spheres;
	while (current)
	{
		if (inter_sphere(cam, ray, current->data))
			color = ((t_sphere *)(current->data))->color;
		current = current->next;
	}
	return (color);
}

int inter_sphere(t_cam *cam, t_vec *ray, t_sphere *sphere)
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
	cam2sphere = v_sub(cam->origin, sphere->center);
	b = 2 * v_dot_product(cam2sphere, ray);
	c = v_dot_product(cam2sphere, cam2sphere) - (pow(sphere->radius, 2));
	discr = (b * b) - (4 * c);
	/* free(cam2sphere); */
	if (discr < 0)
		return (0);
	hit1 = (-b - sqrt(discr)) / 2;
	hit2 = (-b + sqrt(discr)) / 2;
	//choose which distance to return
	/* if ((hit1 * hit2) > 0) */
	if (hit1 > 0)
		return (1);
	else
		return (0);
}
