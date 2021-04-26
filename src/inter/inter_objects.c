#include "minirt.h"

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene)
{
	t_list *current;
	t_obj *cur_obj;
	float ray_len;
	float ray_min;
	t_obj *closest;

	t_vec *norm;
	t_color color;
	t_color ambient;

	ray_min = INFINITY;
	closest = NULL;
	color = -1;
	current = scene->objects;
	while (current)
	{
		cur_obj = current->data;
		if (cur_obj->type == T_SPHERE)
		{
			ray_len = inter_sphere(cam->origin, ray, &cur_obj->obj.sphere);
			if ((ray_len > 0) && (ray_len < ray_min))
			{
				ray_min = ray_len;
				closest = cur_obj;
			}
		}
		current = current->next;
	}

	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity);
	if (closest)
	{
		if (closest->type == T_SPHERE)
		{
			norm = v_sub(v_mult(ray, ray_min), closest->obj.sphere.center);
			v_norm(norm);
			if (scene->lights)
				color = c_mul(closest->obj.sphere.color,
						c_add(ambient,
							calc_lights(norm, scene, ray, ray_min)));
			else
				color = c_mul(ambient, closest->obj.sphere.color);
		}
	}
	return (color);
}

/* t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene) */
/* { */
/* 	t_list *current; */
/* 	t_sphere *sphere; */
/* 	t_plane *plane; */
/* 	float ray_len; */

/* 	t_sphere *sph_closest; */
/* 	t_plane *plane_closest; */
/* 	float ray_min; */

/* 	t_color color; */
/* 	/1* t_color calculated; *1/ */
/* 	t_color ambient; */

/* 	t_list *candidates; */

/* 	t_vec *norm; */

/* 	color = -1; */
/* 	ray_min = INFINITY; */
/* 	ray_len = 0; */
/* 	sph_closest = NULL; */
/* 	plane_closest = NULL; */
/* 	current = scene->spheres; */
/* 	candidates = NULL; */
/* 	while (current) */
/* 	{ */
/* 		sphere = current->data; */
/* 		ray_len = inter_sphere(cam->origin, ray, sphere); */
/* 		if ((ray_len > 0) && (ray_len < ray_min)) */
/* 		{ */
/* 			ray_min = ray_len; */
/* 			sph_closest = sphere; */
/* 		} */
/* 		current = current->next; */
/* 	} */

/* 	ambient = c_mul_scalar(scene->ambient, scene->amb_intensity); */
/* 	if (sph_closest) */
/* 	{ */
/* 		norm = v_sub(v_mult(ray, ray_min), sph_closest->center); */
/* 		v_norm(norm); */
/* 		if (scene->lights) */
/* 			/1* calculated = calc_light_matte(sph_closest, scene->lights->data, ray, ray_min); *1/ */
/* 			color = c_mul(sph_closest->color, */
/* 					c_add(ambient, */
/* 						calc_lights(norm, scene, ray, ray_min))); */
/* 		else */
/* 			color = c_mul(ambient, sph_closest->color); */
/* 		ft_lstadd_back(&candidates, ft_lstnew(cand_new(color, ray_min))); */
/* 	} */

/* 	current = scene->planes; */
/* 	while (current) */
/* 	{ */
/* 		plane = current->data; */
/* 		ray_len = inter_plane(cam->origin, ray, plane); */

/* 		if ((ray_len > 0) && (ray_len < ray_min)) */
/* 			{ */
/* 				ray_min = ray_len; */
/* 				plane_closest = plane; */
/* 				/1* color = plane->color; *1/ */
/* 			} */
/* 		current = current->next; */
/* 	} */
/* 	if (plane_closest) */
/* 	{ */
/* 		if (scene->lights) */
/* 			/1* color = plane_closest->color; *1/ */
/* 			color = c_mul(plane_closest->color, */
/* 					c_add(ambient, */
/* 						calc_lights_2s(plane_closest->norm, scene, ray, ray_min))); */
/* 		else */
/* 			color = c_mul(ambient, plane_closest->color); */
/* 		ft_lstadd_back(&candidates, ft_lstnew(cand_new(color, ray_min))); */
/* 	} */
/* 	return (choose_candidate(&candidates)); */
/* } */
