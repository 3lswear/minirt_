#include "minirt.h"

static int	just_intersect(t_point *start, t_vec *vec, t_list *objects, double max_len)
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
		else if (cur_obj->type == T_CYLIND)
		{
			ray_len = just_get(inter_cylind(start, vec, &cur_obj->obj.cylind, 0));
		}
		if ((ray_len < max_len) && (ray_len > 0))
		{
			free(start);
			free(vec);
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
	result = new_color(0, 0, 0);
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
				calc_light_matte(norm_mod, light, ray_min, cam));

		/* result = c_add(result, */
		/* 	calc_light_matte(norm_mod, light, cam->ray, ray_min, cam)); */
		free(norm_mod);
		current = current->next;
	}
	return (result);
}

/* t_color calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, double ray_min) */
/* { */
/* 	t_list *current; */
/* 	t_color result; */
/* 	t_light *light; */
/* 	/1* t_vec *norm; *1/ */

/* 	current = scene->lights; */
/* 	result = new_color(0, 0, 0); */
/* 	while (current) */
/* 	{ */
/* 		light = current->data; */
/* 		/1* calc_shadow(ray, ray_min, light->coords, scene); *1/ */
/* 			/1* result = BLUE; *1/ */
/* 			/1* /2* return (result); *2/ *1/ */
/* 		/1* /2* 	return (RED); *2/ *1/ */
/* 		/1* else *1/ */
/* 		if (!calc_shadow(ray, ray_min, light->coords, scene, NULL)) */
/* 			result = c_add(result, */
/* 					calc_light_matte(norm, current->data, ray, ray_min, NULL)); */
/* 		current = current->next; */
/* 	} */
/* 	return (result); */
/* } */
