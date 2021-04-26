#include "minirt.h"

t_plane new_plane(t_point *pos, t_vec *norm)
{
	t_plane result;

	result.pos = pos;
	result.norm = norm;
	return (result);
}
