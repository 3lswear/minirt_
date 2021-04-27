#include "minirt.h"

static int just_intersect(t_point *start, t_vec *vec, t_list *objects, float max_len)
{
	t_list *current;
	t_obj *cur_obj;
	float ray_len;

	current = objects;
	while (current)
	{
		cur_obj = current->data;
		if (cur_obj->type == T_SPHERE)
			ray_len = inter_sphere(start, vec, &cur_obj->obj.sphere);
		else if (cur_obj->type == T_PLANE)
			ray_len = inter_plane(start, vec, &cur_obj->obj.plane);
		if ((ray_len < max_len) && (ray_len > 0))
		{
			printf("ray_len => %f, max_len => %f\n", ray_len, max_len);
			return (1);
		}

		current = current->next;
	}
	return (0);
}

int calc_shadow(t_vec *ray, float ray_len, t_point *light_pos, t_scene *scene)
{
	t_point *surface_point;
	t_vec *obj2light;
	float max_len;

	surface_point = v_mult(ray, ray_len * (1 - FLT_EPSILON * 9));
	/* obj2light = v_sub(surface_point, light_pos); */
	obj2light = v_sub(light_pos, surface_point);
	/* obj2light = v_mult(obj2light, 1 - 0.100090); */
	max_len = v_len(obj2light);
	/* max_len = max_len - FLT_EPSILON; */
	v_norm(obj2light);
	return (just_intersect(surface_point, obj2light, scene->objects, max_len));

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
		if (v_dot_product(ray, norm) > 0)
			norm_mod = v_mult(norm, -1);
		else
			norm_mod = v_new(norm->x, norm->y, norm->z);
		/* norm_mod = v_mult(norm, -1); */

		/* calc_shadow(ray, ray_min, light->coords, scene); */
			/* result = BLUE; */
		/* /1* 	return (result); *1/ */
		/* /1* 	return (RED); *1/ */
		/* else */
		if (!calc_shadow(ray, ray_min, light->coords, scene))
			result = c_add(result,
				calc_light_matte(norm_mod, light, ray, ray_min));
		current = current->next;
	}
	return (result);
}

t_color calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, float ray_min)
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
		if (!calc_shadow(ray, ray_min, light->coords, scene))
			result = c_add(result,
					calc_light_matte(norm, current->data, ray, ray_min));
		current = current->next;
	}
	return (result);
}
