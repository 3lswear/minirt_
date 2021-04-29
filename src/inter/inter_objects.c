#include "minirt.h"

t_color color_closest(t_scene *scene, t_cam *cam, t_obj *closest, t_color ambient, double ray_min)
{
	t_point *surface_point;
	t_vec *norm;
	t_color color;

	color = -1;
	if (closest->type == T_SPHERE)
	{
		surface_point = v_mult(cam->ray, ray_min);
		surface_point = v_add(surface_point, cam->origin);
		norm = v_sub(surface_point, closest->obj.sphere.center);
		v_norm_inplace(norm);
		if (scene->lights)
			color = c_mul(closest->obj.sphere.color,
					c_add(ambient,
						calc_lights_2s(norm, scene, cam->ray, ray_min, cam)));
		else
			color = c_mul(ambient, closest->obj.sphere.color);
		free(norm);
		free(surface_point);
	}
	else if (closest->type == T_PLANE)
	{
		if (scene->lights)
			color = c_mul(closest->obj.plane.color,
					c_add(ambient,
						calc_lights_2s(closest->obj.plane.norm, scene, cam->ray, ray_min, cam)));
		else
			color = c_mul(ambient, closest->obj.plane.color);
	}
	else if (closest->type == T_TRIANG)
	{
		if (scene->lights)
			color = c_mul(closest->obj.triang.color,
					c_add(ambient,
						calc_lights_2s(closest->obj.triang.norm, scene, cam->ray, ray_min, cam)));
		else
			color = c_mul(ambient, closest->obj.triang.color);
	}
	return (color);
}

t_color inter_objects(t_cam *cam, t_scene *scene)
{
	t_list *current;
	t_obj *cur_obj;
	double ray_len;
	double ray_min;
	t_obj *closest;
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
			hit = inter_sphere(cam->origin, cam->ray, &cur_obj->obj.sphere);
			ray_len = get_positive(hit);
		}
		else if (cur_obj->type == T_PLANE)
			ray_len = inter_plane(cam->origin, cam->ray, &cur_obj->obj.plane);
		else if (cur_obj->type == T_TRIANG)
			ray_len = inter_triang(cam->origin, cam->ray, &cur_obj->obj.triang);
		if ((ray_len > 0) && (ray_len < ray_min))
		{
			ray_min = ray_len;
			closest = cur_obj;
		}
		current = current->next;
	}
	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (closest)
		color = color_closest(scene, cam, closest, ambient, ray_min);
	return (color);
}
