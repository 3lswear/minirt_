#include "minirt.h"

float inter_square(t_point *origin, t_vec *ray, t_square *square)
{
	float ray_len;
	
	t_plane plane;
	plane.color = BLACK;
	plane.norm = square->norm;
	plane.pos = square->pos;
	ray_len = inter_plane(origin, ray, &plane);
	if (ray_len < 0)
		return (ray_len);
	return (0);

}
