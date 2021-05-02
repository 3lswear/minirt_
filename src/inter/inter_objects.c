#include "minirt.h"

t_color color_closest(t_scene *scene, t_cam *cam, t_obj *closest, t_color ambient, double ray_min)
{
	t_point *surface_point;
	t_vec *norm;
	t_color color;

	/* color = new_color(-1, -1, -1); */
	if (scene->lights)
	{
		if (closest->type == T_SPHERE)
		{
			surface_point = v_mult(cam->ray, ray_min);
			v_add_inplace(surface_point, cam->origin);
			norm = v_sub(surface_point, closest->obj.sphere.center);
			v_norm_inplace(norm);
			color = c_mul(closest->color, c_add(ambient,
						calc_lights_2s(norm, scene, ray_min, cam)));
			free(norm);
			free(surface_point);
		}
		else if (closest->type == T_PLANE)
			color = c_mul(closest->color, c_add(ambient,
						calc_lights_2s(closest->obj.plane.norm, scene, ray_min, cam)));
		else if (closest->type == T_TRIANG)
			color = c_mul(closest->color, c_add(ambient,
						calc_lights_2s(closest->obj.triang.norm, scene, ray_min, cam)));
		else if (closest->type == T_SQUARE)
			color = c_mul(closest->color, c_add(ambient,
						calc_lights_2s(closest->obj.square.norm, scene, ray_min, cam)));
		else if (closest->type == T_CYLIND)
		{
			color = c_mul(closest->color, c_add(ambient,
						calc_lights_2s(closest->obj.cylind.cur_norm, scene, ray_min, cam)));
			/* free(closest->obj.cylind.cur_norm); */

		}
		else
			color = c_mul(ambient, closest->color);
	}
	else
		color = c_mul(ambient, closest->color);
	return (color);
}

t_color inter_objects(t_cam *cam, t_scene *scene)
{
	t_list *current;
	t_obj *cur_obj;
	double ray_len;
	double ray_min;
	t_obj *closest;
	t_color ambient;

	ray_min = INFINITY;
	closest = NULL;
	current = scene->objects;
	while (current)
	{
		cur_obj = current->data;
		if (cur_obj->type == T_SPHERE)
			ray_len = get_positive(inter_sphere(cam->origin,
						cam->ray, &cur_obj->obj.sphere));
		else if (cur_obj->type == T_PLANE)
			ray_len = inter_plane(cam->origin, cam->ray, &cur_obj->obj.plane);
		else if (cur_obj->type == T_TRIANG)
			ray_len = inter_triang(cam->origin, cam->ray, &cur_obj->obj.triang);
		else if (cur_obj->type == T_SQUARE)
			ray_len = inter_square(cam->origin, cam->ray, &cur_obj->obj.square);
		else if (cur_obj->type == T_CYLIND)
			ray_len = just_get(inter_cylind(cam->origin, cam->ray, &cur_obj->obj.cylind));
		if ((ray_len > 0) && (ray_len < ray_min))
		{
			ray_min = ray_len;
			closest = cur_obj;
		}
		current = current->next;
	}
	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (closest)
		return(color_closest(scene, cam, closest, ambient, ray_min));
	else
		return (new_color(-1, -1, -1));
}
