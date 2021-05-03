#include "minirt.h"

void	lst_spheres(t_scene *scene, char **data)
{
	t_sphere	sphere;
	t_obj		*object;

	sphere = new_sphere(
			parse_point(data[1]),
			parse_doubles(data[2])
			);
	sphere.color = parse_color(data[3]);
	object = new_object(T_SPHERE, NULL);
	object->obj.sphere = sphere;
	object->color = sphere.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	lst_planes(t_scene *scene, char **data)
{
	t_plane	plane;
	t_obj	*object;

	plane = new_plane(
			parse_point(data[1]),
			parse_vec(data[2]),
			/* parse_norm(data[2]), */
			parse_color(data[3])
			);
	/* maybe remove */
	v_norm_inplace(plane.norm);
	object = new_object(T_PLANE, NULL);
	object->obj.plane = plane;
	object->color = plane.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	lst_squares(t_scene *scene, char **data)
{
	t_obj	*object;

	object = new_object(T_SQUARE, NULL);
	object->obj.square = new_square(
			parse_point(data[1]),
			/* parse_norm(data[2]), */
			parse_vec(data[2]),
			parse_flpos(data[3]),
			parse_color(data[4])
			);
	v_norm_inplace(object->obj.square.norm);
	object->obj.square.hside = object->obj.square.side / 2.0;
	sq_get_vertices(&object->obj.square);
	object->color = object->obj.square.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	lst_triangs(t_scene *scene, char **data)
{
	t_obj	*object;

	object = new_object(T_TRIANG, NULL);
	object->obj.triang = new_triang(
			parse_point(data[1]),
			parse_point(data[2]),
			parse_point(data[3]),
			parse_color(data[4])
			);
	object->color = object->obj.triang.color;
	object->obj.triang.norm = triang_get_norm(&object->obj.triang);
	/* printf("tri color => %X\n", object->obj.triang.color); */
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	lst_cylinds(t_scene *scene, char **data)
{
	t_obj	*object;

	object = new_object(T_CYLIND, NULL);
	object->obj.cylind = new_cylind(
			parse_point(data[1]),
			parse_norm(data[2]),
			parse_flpos(data[3]),
			parse_flpos(data[4])
			);
	object->obj.cylind.color = parse_color(data[5]);
	object->obj.cylind.rad = object->obj.cylind.diam / 2.0;
	object->obj.cylind.cur_norm = NULL;
	object->color = object->obj.cylind.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}
