#include "minirt.h"

double	inter_plane(t_vec *origin, t_vec *ray, t_plane *plane)
{
	double	t;
	t_vec	*tmp;

	tmp = v_sub(plane->pos, origin);
	t = (v_dot_product(tmp, plane->norm))
		/ (v_dot_product(ray, plane->norm));
	free(tmp);
	return (t);
}
