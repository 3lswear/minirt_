#include "minirt.h"

t_plane new_plane(t_point *pos, t_vec *norm, t_color color)
{
	t_plane result;

	result.pos = pos;
	result.norm = norm;
	result.color = color;
	return (result);
}
