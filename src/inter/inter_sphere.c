#include "minirt.h"

t_color calc_light_matte(t_vec *n, t_light *light, t_vec *ray, float ray_len)
{
	t_point *surface_point;
	/* t_vec *n; */
	t_vec *l;
	float strength;


	surface_point = v_mult(ray, ray_len);
	l = v_sub(light->coords, surface_point);
	/* n = v_sub(surface_point, sphere->center); */
	v_norm(n);
	/* printf("surface_point\t-> %f,%f,%f\n", surface_point->x, surface_point->y, surface_point->z); */
	/* printf("light_point\t-> %f,%f,%f\n", l_norm->x, l_norm->y, l_norm->z); */
	strength = v_dot_product(n, l) / (v_len(l) * v_len(n));
	/* printf("strength => %f\n", strength); */
	/* printf("color =>%X\n", color); */
	free(surface_point);
	if (v_dot_product(n, l) > 0)
	{
		free(l);
		/* free(n); */
		return(c_mul_scalar(light->color, (light->brightess * strength)));
	}
	else
	{
		free(l);
		/* free(n); */
		return (0);
	}
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

t_color calc_lights_2s(t_vec *norm, t_scene *scene, t_vec *ray, float ray_min)
{
	t_list *current;
	t_color result;
	/* t_vec *norm; */
	t_light *light;
	t_vec *norm_mod;

	current = scene->lights;
	result = BLACK;
	while (current)
	{
		light = current->data;
		/* LEAKZ */
		if (v_dot_product(v_sub(light->coords, ray), norm) < 0)
			norm_mod = v_mult(norm, -1);
		else
			norm_mod = v_new(norm->x, norm->y, norm->z);

		result = c_add(result,
				calc_light_matte(norm_mod, current->data, ray, ray_min));
		current = current->next;
	}
	return (result);
}

t_color calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, float ray_min)
{
	t_list *current;
	t_color result;
	/* t_vec *norm; */

	current = scene->lights;
	result = BLACK;
	while (current)
	{
		result = c_add(result,
				calc_light_matte(norm, current->data, ray, ray_min));
		current = current->next;
	}
	return (result);
}

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	t_list *current;
	t_sphere *sphere;
	t_plane *plane;
	float ray_len;

	t_sphere *sph_closest;
	t_plane *plane_closest;
	float ray_min;

	t_color color;
	/* t_color calculated; */
	t_color ambient;

	t_list *candidates;

	t_vec *norm;

	color = -1;
	ray_min = INFINITY;
	ray_len = 0;
	sph_closest = NULL;
	plane_closest = NULL;
	current = scene->spheres;
	candidates = NULL;
	while (current)
	{
		sphere = current->data;
		ray_len = inter_sphere(cam->origin, ray, sphere);
		if ((ray_len > 0) && (ray_len < ray_min))
		{
			ray_min = ray_len;
			sph_closest = sphere;
		}
		current = current->next;
	}

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (sph_closest)
	{
		norm = v_sub(v_mult(ray, ray_min), sph_closest->center);
		v_norm(norm);
		if (scene->lights)
			/* calculated = calc_light_matte(sph_closest, scene->lights->data, ray, ray_min); */
			color = c_mul(sph_closest->color,
					c_add(ambient,
						calc_lights(norm, scene, ray, ray_min)));
		else
			color = c_mul(ambient, sph_closest->color);
		ft_lstadd_back(&candidates, ft_lstnew(cand_new(color, ray_min)));
	}

	current = scene->planes;
	while (current)
	{
		plane = current->data;
		ray_len = inter_plane(cam->origin, ray, plane);

		if ((ray_len > 0) && (ray_len < ray_min))
			{
				ray_min = ray_len;
				plane_closest = plane;
				color = plane->color;
			}
		current = current->next;
	}
	if (plane_closest)
	{
		if (scene->lights)
			/* color = plane_closest->color; */
			color = c_mul(plane_closest->color,
					c_add(ambient,
						calc_lights_2s(plane_closest->norm, scene, ray, ray_min)));
		else
			color = c_mul(ambient, plane_closest->color);
		ft_lstadd_back(&candidates, ft_lstnew(cand_new(color, ray_min)));
	}
	return (choose_candidate(&candidates));
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
