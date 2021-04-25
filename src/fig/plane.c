#include "minirt.h"

t_plane *new_plane(t_point *pos, t_vec *norm)
{
	t_plane *result;

	result = ft_calloc(1, sizeof(t_plane));
	if (!result)
		handle_error(-1);
	result->pos = pos;
	result->norm = norm;
	return (result);
}
