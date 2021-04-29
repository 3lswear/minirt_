#include "minirt.h"

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	t_list *current;
	t_obj *cur_obj;
	float ray_len;
	float ray_min;
	t_obj *closest;

	t_vec *norm;
	t_vec *tmp;
	t_color color;
	t_color ambient;

	t_hit hit;

	ray_min = INFINITY;
	closest = NULL;
	color = -1;
	current = scene->objects;
	while (current)
	{
		cur_obj = current->data;
		if (cur_obj->type == T_SPHERE)
		{
			hit = inter_sphere(cam->origin, ray, &cur_obj->obj.sphere);
			ray_len = get_positive(hit);
		}
		else if (cur_obj->type == T_PLANE)
			ray_len = inter_plane(cam->origin, ray, &cur_obj->obj.plane);
		else if (cur_obj->type == T_TRIANG)
			ray_len = inter_triang(cam->origin, ray, &cur_obj->obj.triang);
		if ((ray_len > 0) && (ray_len < ray_min))
		{
			ray_min = ray_len;
			closest = cur_obj;
		}
		current = current->next;
	}

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (closest)
	{
		if (closest->type == T_SPHERE)
		{
			tmp = v_mult(ray, ray_min);
			norm = v_sub(tmp, closest->obj.sphere.center);
			v_norm(norm);
			if (scene->lights)
				color = c_mul(closest->obj.sphere.color,
						c_add(ambient,
							calc_lights_2s(norm, scene, ray, ray_min)));
			else
				color = c_mul(ambient, closest->obj.sphere.color);
			free(norm);
			free(tmp);
		}
		else if (closest->type == T_PLANE)
		{
			if (scene->lights)
				color = c_mul(closest->obj.plane.color,
						c_add(ambient,
							calc_lights_2s(closest->obj.plane.norm, scene, ray, ray_min)));
			else
				color = c_mul(ambient, closest->obj.plane.color);
		}
		else if (closest->type == T_TRIANG)
		{
			if (scene->lights)
				color = c_mul(closest->obj.triang.color,
						c_add(ambient,
							calc_lights_2s(closest->obj.triang.norm, scene, ray, ray_min)));
			else
				color = c_mul(ambient, closest->obj.triang.color);
		}
	}
	return (color);
}
