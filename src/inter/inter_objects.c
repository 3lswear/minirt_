#include "minirt.h"

t_color	return_sph_color(t_scene *scene, t_cam *cam, t_obj *closest,
			double ray_min)
{
	t_color	color;
	t_vec	*norm;
	t_point	*surface_point;
	t_color	ambient;

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	surface_point = v_mult(cam->ray, ray_min);
	v_add_inplace(surface_point, cam->origin);
	norm = v_sub(surface_point, closest->obj.sphere.center);
	v_norm_inplace(norm);
	color = c_mul(closest->color, c_add(ambient, calc_lights_2s
				(norm, scene, ray_min, cam)));
	free(norm);
	free(surface_point);
	return (color);
}

t_color	return_cy_color(t_scene *scene, t_cam *cam, t_obj *cl, double ray_min)
{
	t_color	ambient;
	t_color	color;

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	color = c_mul(cl->color, c_add(ambient, calc_lights_2s
				(cl->obj.cylind.cur_norm, scene, ray_min, cam)));
	free(cl->obj.cylind.cur_norm);
	return (color);
}

t_color	color_closest(t_scene *scene, t_cam *cam, t_obj *cl,
			double ray_min)
{
	t_color	color;
	t_color	ambient;

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (scene->lights)
	{
		if (cl->type == T_SPHERE)
			color = return_sph_color(scene, cam, cl, ray_min);
		else if (cl->type == T_PLANE)
			color = c_mul(cl->color, c_add(ambient, calc_lights_2s
						(cl->obj.plane.norm, scene, ray_min, cam)));
		else if (cl->type == T_TRIANG)
			color = c_mul(cl->color, c_add(ambient, calc_lights_2s
						(cl->obj.triang.norm, scene, ray_min, cam)));
		else if (cl->type == T_SQUARE)
			color = c_mul(cl->color, c_add(ambient, calc_lights_2s
						(cl->obj.square.norm, scene, ray_min, cam)));
		else if (cl->type == T_CYLIND)
			color = return_cy_color(scene, cam, cl, ray_min);
		else
			color = c_mul(ambient, cl->color);
	}
	else
		color = c_mul(ambient, cl->color);
	return (color);
}

double	i_objects(t_cam *cam, t_scene *scene, t_obj *cur_obj)
{
	double	ray_len;

	(void)scene;
	ray_len = 0;
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
		ray_len = just_get(inter_cylind(cam->origin, cam->ray,
					&cur_obj->obj.cylind, 1));
	return (ray_len);
}

t_color	inter_objects(t_cam *cam, t_scene *scene)
{
	t_list	*current;
	double	ray_min;
	t_obj	*closest;
	t_color	ambient;
	double	ray_len;

	ray_min = INFINITY;
	closest = NULL;
	current = scene->objects;
	while (current)
	{
		ray_len = i_objects(cam, scene, current->data);
		if ((ray_len > 0) && (ray_len < ray_min))
		{
			ray_min = ray_len;
			closest = current->data;
		}
		current = current->next;
	}
	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (closest)
		return (color_closest(scene, cam, closest, ray_min));
	else
		return (new_color(-1, -1, -1));
}
