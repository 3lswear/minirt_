#include "minirt.h"

t_triang new_triang(t_point *a, t_point *b, t_point *c, t_color color)
{
	t_triang result;

	result.a = a;
	result.b = b;
	result.c = c;
	result.color = color;
	return (result);
}
