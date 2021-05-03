#include "minirt.h"

void	free_sphere(t_obj *obj)
{
	t_sphere	*sphere;

	sphere = &obj->obj.sphere;
	free(sphere->center);
}

void	free_plane(t_obj *obj)
{
	t_plane	*plane;

	plane = &obj->obj.plane;
	free(plane->norm);
	free(plane->pos);
}

void	free_triang(t_obj *obj)
{
	t_triang	*triang;

	triang = &obj->obj.triang;
	free(triang->a);
	free(triang->b);
	free(triang->c);
	free(triang->norm);
	free(triang->edge1);
	free(triang->edge2);
}

void	free_square(t_obj *obj)
{
	t_square	*sq;

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
	t_cylind	*cy;

	cy = &obj->obj.cylind;
	free4(cy->norm, cy->pos, NULL, NULL);
}
