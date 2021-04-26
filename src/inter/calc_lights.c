#include "minirt.h"

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
