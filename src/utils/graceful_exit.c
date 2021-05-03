#include "minirt.h"

void	clean_objects(void *data)
{
	t_obj	*object;

	object = data;
	if (object->type == T_SPHERE)
		free_sphere(object);
	else if (object->type == T_PLANE)
		free_plane(object);
	else if (object->type == T_TRIANG)
		free_triang(object);
	else if (object->type == T_SQUARE)
		free_square(object);
	else if (object->type == T_CYLIND)
		free_cylind(object);
	free(object);
}

void	clean_cams(void *data)
{
	t_cam	*cam;

	cam = data;
	free(cam->dir);
	free(cam->origin);
	free(cam);
}

void	clean_lights(void *data)
{
	t_light	*light;

	light = data;
	free(light->coords);
	free(light);
}

void	graceful_exit(t_win *win, t_scene *scene, int save_arg)
{
	ft_lstclear(&scene->objects, clean_objects);
	ft_lstclear(&scene->cams, clean_cams);
	ft_lstclear(&scene->lights, clean_lights);
	free(scene);
	mlx_destroy_image(win->mlx, win->img);
	if (!save_arg)
	{
		mlx_destroy_window(win->mlx, win->win);
		mlx_destroy_display(win->mlx);
	}
	free(win->mlx);
	exit(0);
}

void	exit_by_close(t_win *win, t_scene *scene)
{
	(void)scene;
	(void)win;
	exit(0);
}
