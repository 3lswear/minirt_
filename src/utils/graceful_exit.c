#include "minirt.h"

void free_sphere(t_obj *obj)
{
	t_sphere *sphere;

	sphere = &obj->obj.sphere;
	free(sphere->center);
	free(obj);
}

void free_plane(t_obj *obj)
{
	t_plane *plane;

	plane = &obj->obj.plane;
	free(plane->norm);
	free(plane->pos);
	free(obj);
}

void clean_objects(void *data)
{
	t_obj *object;

	object = data;
	if (object->type == T_SPHERE)
		free_sphere(object);
	else if (object->type == T_PLANE)
		free_plane(object);

}

void clean_cams(void *data)
{
	t_cam *cam;

	cam = data;
	free(cam->dir);
	free(cam->origin);
	free(cam);
}

void clean_lights(void *data)
{
	t_light *light;

	light = data;
	free(light->coords);
	free(light);
}

void graceful_exit(t_win *win, t_scene *scene)
{
	ft_lstclear(&scene->objects, clean_objects);
	ft_lstclear(&scene->cams, clean_cams);
	ft_lstclear(&scene->lights, clean_lights);
	free(scene);

	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	exit(0);
}

