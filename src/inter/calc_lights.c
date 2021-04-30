#include "minirt.h"

static	int just_intersect(t_point *start, t_vec *vec, t_list *objects, double max_len)
{
	t_list	*current;
	t_obj	*cur_obj;
	double	ray_len;
	t_hit	hit;

	current = objects;
	while (current)
	{
		cur_obj = current->data;
		if (cur_obj->type == T_SPHERE)
		{
			hit = inter_sphere(start, vec, &cur_obj->obj.sphere);
			ray_len = just_get(hit);
		}
		else if (cur_obj->type == T_PLANE)
			ray_len = inter_plane(start, vec, &cur_obj->obj.plane);
		else if (cur_obj->type == T_TRIANG)
			ray_len = inter_triang(start, vec, &cur_obj->obj.triang);
		else if (cur_obj->type == T_SQUARE)
			ray_len = inter_square(start, vec, &cur_obj->obj.square);
		/* if ((ray_len < max_len) && (ray_len > max_len * FLT_EPSILON * 100)) */
		if ((ray_len < max_len) && (ray_len > 0))
		{
			/* if (hit.a * hit.b != 0) */
			/* { */
			/* 	printf("hits => %f	%f\n", hit.a, hit.b); */
			/* 	printf("ray_len =>\t%f\n", ray_len); */
			/* } */
			free(start);
			free(vec);
			/* printf("ray_len => %f, max_len => %f\n", ray_len, max_len); */
			return (1);
		}

		current = current->next;
	}
	free(start);
	free(vec);
	return (0);
}

int	calc_shadow(t_vec *ray, double ray_len, t_point *light_pos, t_scene *scene, t_cam *cam)
{
	t_point	*surface_point;
	t_vec	*obj2light;
	double	max_len;

	surface_point = v_mult(ray, ray_len * (1 - FLT_EPSILON * 1));
	/* print_vec(surface_point, "surface_point"); */
	v_add_inplace(surface_point, cam->origin);
	/* print_vec(surface_point, "surface_point after add"); */
	/* obj2light = v_sub(surface_point, light_pos); */
	obj2light = v_sub(light_pos, surface_point);
	/* obj2light = v_mult(obj2light, 1 - 0.100090); */
	max_len = v_len(obj2light);
	/* max_len = max_len - FLT_EPSILON; */
	v_norm_inplace(obj2light);
	return (just_intersect(surface_point, obj2light, scene->objects, max_len));

}

t_color	calc_lights_2s(t_vec *norm, t_scene *scene, double ray_min, t_cam *cam)
{
	t_list	*current;
	t_color	result;
	t_light	*light;
	t_vec	*norm_mod;

	current = scene->lights;
	result = BLACK;
	while (current)
	{
		light = current->data;
		/* LEAKZ */
		if (v_dot_product(cam->ray, norm) > 0)
			norm_mod = v_mult(norm, -1);
		else
			norm_mod = v_new(norm->x, norm->y, norm->z);

		if (!calc_shadow(cam->ray, ray_min, light->coords, scene, cam))
			result = c_add(result,
				calc_light_matte(norm_mod, light, cam->ray, ray_min, cam));

		/* result = c_add(result, */
		/* 	calc_light_matte(norm_mod, light, ray, ray_min, cam)); */
		free(norm_mod);
		current = current->next;
	}
	return (result);
}

t_color calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, double ray_min)
{
	t_list *current;
	t_color result;
	t_light *light;
	/* t_vec *norm; */

	current = scene->lights;
	result = BLACK;
	while (current)
	{
		light = current->data;
		/* calc_shadow(ray, ray_min, light->coords, scene); */
			/* result = BLUE; */
			/* /1* return (result); *1/ */
		/* /1* 	return (RED); *1/ */
		/* else */
		if (!calc_shadow(ray, ray_min, light->coords, scene, NULL))
			result = c_add(result,
					calc_light_matte(norm, current->data, ray, ray_min, NULL));
		current = current->next;
	}
	return (result);
}
