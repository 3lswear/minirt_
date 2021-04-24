#include "minirt.h"

t_color argb_color(int r, int g, int b)
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

t_color c_add(t_color color1, int color2)
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

t_color c_mul_scalar(t_color color, float mul)
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

t_color c_mul(t_color color1, t_color color2)
{
	t_color result;
	double channel;
	color1 = color1 & WHITE;
	color2 = color2 & WHITE;

	channel = idiv((color1 >> 16), 255) * idiv(color2 >> 16, 255);
	/* channel = ceil(channel); */
	result = channel * 255;
	result = result << 8;
	channel = idiv((color1 & G_MASK) >> 8, 255)
		* idiv((color2 & G_MASK) >> 8, 255);
	/* channel = ceil(channel); */
	result += channel * 255;
	result = result << 8;
	channel = idiv((color1 & B_MASK), 255) * idiv(color2 & B_MASK, 255);
	/* channel = ceil(channel); */
	result += channel * 255;
	return (result);
}

/* int argb_color(t_color color) */
/* { */
/* 	int result; */
/* 	int channel; */

/* 	channel = color.r * 0xFF; */
/* 	if (channel > 0xFF) */
/* 		channel = 0xFF; */
/* 	result = channel; */
/* 	result = result << 8; */
/* 	channel = color.g * 0xFF; */
/* 	if (channel > 0xFF) */
/* 		channel = 0xFF; */
/* 	result += channel; */
/* 	result = result << 8; */
/* 	channel = color.b * 0xFF; */
/* 	if (channel > 0xFF) */
/* 		channel = 0xFF; */
/* 	result += channel; */
/* 	return (result); */
/* } */

/* t_color c_add(t_color color1, t_color color2) */
/* { */
/* 	t_color result; */
/* 	result.r = color1.r + color2.r; */
/* 	if (result.r > 1) */
/* 		result.r = 1; */
/* 	result.g = color1.g + color2.g; */
/* 	if (result.g > 1) */
/* 		result.g = 1; */
/* 	result.b = color1.b + color2.b; */
/* 	if (result.b > 1) */
/* 		result.b = 1; */
/* 	return (result); */
/* } */

/* t_color c_mul_scalar(t_color color, float mul) */
/* { */
/* 	t_color result; */
/* 	result.r = color.r * mul; */
/* 	if (result.r > 1) */
/* 		result.r = 1; */
/* 	result.g = color.g * mul; */
/* 	if (result.g > 1) */
/* 		result.g = 1; */
/* 	result.b = color.b * mul; */
/* 	if (result.b > 1) */
/* 		result.b = 1; */
/* 	return (result); */
/* } */

/* t_color c_mul(t_color color1, t_color color2) */
/* { */
/* 	t_color result; */

/* 	result.r = color1.r * color2.r; */
/* 	if (result.r > 1) */
/* 		result.r = 1; */
/* 	result.g = color1.g * color2.g; */
/* 	if (result.g > 1) */
/* 		result.g = 1; */
/* 	result.b = color1.b * color2.b; */
/* 	if (result.b > 1) */
/* 		result.b = 1; */
/* 	return (result); */
/* } */

t_color calc_light_matte(t_sphere *sphere, t_light *light, t_vec *ray, float ray_len)
{
	t_point *surface_point;
	t_vec *n;
	t_vec *l;
	float strength;


	surface_point = v_mult(ray, ray_len);
	l = v_sub(light->coords, surface_point);
	n = v_sub(surface_point, sphere->center);
	v_norm(n);
	/* printf("surface_point\t-> %f,%f,%f\n", surface_point->x, surface_point->y, surface_point->z); */
	/* printf("light_point\t-> %f,%f,%f\n", l_norm->x, l_norm->y, l_norm->z); */
	strength = v_dot_product(n, l) / (v_len(l) * v_len(n));
	/* printf("strength => %f\n", strength); */
	/* printf("color =>%X\n", color); */
	if (v_dot_product(n, l) > 0)
		return(c_mul_scalar(light->color, (light->brightess * strength)));
	else
		return (0);
}

t_color calc_light_shiny(t_sphere *sphere, t_light *light, t_vec *ray, float ray_len)
{
	t_point *surface_point;
	t_vec *n;
	t_vec *l;
	t_vec *r;
	t_vec *v;
	float strength;

	surface_point = v_mult(ray, ray_len);
	v = v_mult(surface_point, -1);
	l = v_sub(light->coords, surface_point);
	n = v_sub(surface_point, sphere->center);
	v_norm(n);
	r = v_sub(v_mult(n, 2 * v_dot_product(n, l)), l);
	/* strength = v_dot_product(n, l) / (v_len(l) * v_len(n)); */
	strength = pow(v_dot_product(r, v) / (v_len(r) * v_len(v)), SHININESS);
	if (v_dot_product(r, v) > 0)
	{
		printf("strength => %f\n", strength);
		printf("bri * stre => %f\n", light->brightess * strength);
		return(c_mul_scalar(light->color, (light->brightess * strength)));
	}
	else
		return (0);
}

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	t_list *current;
	t_sphere *sphere;
	float ray_len;

	t_sphere *sph_closest;
	float ray_min;

	t_color color;
	t_color calculated;
	t_color ambient;

	color = -1;
	ray_min = INFINITY;
	ray_len = 0;
	sph_closest = NULL;
	current = scene->spheres;
	while (current)
	{
		sphere = current->data;
		/* if (ray_len_new < ray_len) */

		ray_len = inter_sphere(cam->origin, ray, sphere);
		if (ray_len > 0)
		{
			if (ray_len < ray_min)
			{
				ray_min = ray_len;
				sph_closest = sphere;
			}
		}
		current = current->next;
	}
	if (ray_min < INFINITY)
	{
		ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);

		if (scene->light)
		{
			calculated = calc_light_matte(sph_closest, scene->light, ray, ray_min);
			color = c_mul(sph_closest->color,
					c_add(ambient, calculated));
		}
		else
			color = c_mul(sph_closest->color, ambient);

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
