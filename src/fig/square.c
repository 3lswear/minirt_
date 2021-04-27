#include "minirt.h"

t_square new_square(t_point *pos, t_vec *norm, float side, t_color color)
{
	t_square result;

	result.pos = pos;
	result.norm = norm;
	result.side = side;
	result.color = color;
	return (result);
}
