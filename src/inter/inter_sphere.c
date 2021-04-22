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

	channel = (color1 & R_MASK) + (color2 & R_MASK);
	if (channel > R_MASK)
		channel = R_MASK;
	result = channel;
	channel = (color1 & G_MASK) + (color2 & G_MASK);
	if (channel > G_MASK)
		channel = G_MASK;
	result += channel;
	channel = (color1 & B_MASK) + (color2 & B_MASK);
	if (channel > B_MASK)
		channel = B_MASK;
	result += channel;

	return (result);
}

int c_mul(int color, float mul)
{
	int result;

	if (mul > 1)
		return (color);
	result = (color >> 16) * mul;
	result = result << 8;
	result += ((color & G_MASK) >> 8) * mul;
	result = result << 8;
	result += (color & B_MASK) * mul;
	return (result);
}

int calc_light(t_sphere *sphere, t_light *light, t_vec *ray, float ray_len)
{
	t_point *surface_point;
	t_vec *n;
	t_vec *l;
	float mult;


	surface_point = v_mult(ray, ray_len);
	l = v_sub(light->coords, surface_point);
	n = v_sub(surface_point, sphere->center);
	v_norm(n);
	/* printf("surface_point\t-> %f,%f,%f\n", surface_point->x, surface_point->y, surface_point->z); */
	/* printf("light_point\t-> %f,%f,%f\n", l_norm->x, l_norm->y, l_norm->z); */
	mult = v_dot_product(n, l) / (v_len(l) * v_len(n));
	/* printf("mult => %f\n", mult); */
	/* printf("color =>%X\n", color); */
	if (mult > 0)
		return(c_mul(light->color, (light->brightess * mult)));
	else
		return (0);
}

int inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	int color;
	t_list *current;
	t_sphere *sphere;
	float ray_len;
	/* float ray_len_new; */

	color = -1;
	ray_len = 0;
	current = scene->spheres;
	while (current)
	{
		sphere = current->data;
		/* if (ray_len_new < ray_len) */

		ray_len = inter_sphere(cam->origin, ray, current->data);
		if (ray_len > 0)
		{
			color = c_add(sphere->color, scene->ambient);
			if (scene->light)
				color = c_add(color, calc_light(sphere, scene->light, ray, ray_len));
			if (color > 0)
			{
				return (color);
			}
		}
		current = current->next;
	}
	return (color);
}

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
	c = v_dot_product(cam2sphere, cam2sphere) - (pow(sphere->radius, 2));
	discr = (b * b) - (4 * c);
	/* free(cam2sphere); */
	if (discr < 0)
		return (0);
	hit1 = (-b - sqrt(discr)) / 2;
	hit2 = (-b + sqrt(discr)) / 2;
	//choose which distance to return
	/* if ((hit1 * hit2) > 0) */
	/* ОПТИМИЗИРОВАТЬ */
	if (hit1 > 0 && hit2 > 0)
	{
		if (hit1 > hit2)
			return (hit2);
		else
			return (hit1);
	}
	else if ((hit1 * hit2) < 0)
	{
		if (hit1 > 0)
			return (hit1);
		else
			return (hit2);
	}
	else
		return (0);
}
