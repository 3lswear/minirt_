#include "minirt.h"

int argb_color(int r, int g, int b)
{
	int color;

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	color = 0;
	color += r;
	color = color << 8;
	color += g;
	color = color << 8;
	color += b;
	/* printf("color is %X\n", color); */
	return (color);
}

int c_add(int color1, int color2)
{
	int result;
	int channel;
	/* 0xAARRGGBB */

	channel = (color1 & 0x00FF0000) + (color2 & 0x00FF0000);
	if (channel > 0x00FF0000)
		channel = 0x00FF0000;
	result = channel;
	channel = (color1 & 0x0000FF00) + (color2 & 0x0000FF00);
	if (channel > 0x0000FF00)
		channel = 0x0000FF00;
	result += channel;
	channel = (color1 & 0x000000FF) + (color2 & 0x000000FF);
	if (channel > 0x000000FF)
		channel = 0x000000FF;
	result += channel;

	return (result);
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
			color = c_add(((t_sphere *)(current->data))->color, scene->ambient);
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
