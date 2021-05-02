#include "minirt.h"

void free_sphere(t_obj *obj)
{
	t_sphere *sphere;

	sphere = &obj->obj.sphere;
	free(sphere->center);
}

void free_plane(t_obj *obj)
{
	t_plane *plane;

	plane = &obj->obj.plane;
	free(plane->norm);
	free(plane->pos);
}

void free_triang(t_obj *obj)
{
	t_triang *triang;

	triang = &obj->obj.triang;
	free(triang->a);
	free(triang->b);
	free(triang->c);
	free(triang->norm);
	free(triang->edge1);
	free(triang->edge2);
}

void free_square(t_obj *obj)
{
	t_square *sq;

	sq = &obj->obj.square;
	free(sq->a);
	free(sq->b);
	free(sq->c);
	free(sq->d);
	free(sq->norm);
	free(sq->pos);
}

void	free_cylind(t_obj *obj)
{
	t_cylind *cy;

	cy = &obj->obj.cylind;
	free4(cy->norm, cy->pos, NULL, NULL);
}

void clean_objects(void *data)
{
	t_obj *object;

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
	free(win->mlx);
	exit(0);
}

