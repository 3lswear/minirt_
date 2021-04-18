#include "minirt.h"

t_cam *new_cam(t_vec *origin, t_vec *dir, float fov)
{
	t_cam *result;
	result = malloc(sizeof(t_cam));
	if (!result)
		handle_error(-1);
	result->origin = origin;
	result->dir = dir;
	result->fov = fov;
	return (result);
}
