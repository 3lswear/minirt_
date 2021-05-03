#include "minirt.h"

t_scene *new_scene(t_cam *cam)
{
	t_scene *result;

	result = malloc(sizeof(t_scene));
	if (!result)
		handle_error(-1, -1);
	(void)*cam;
	result->cams = NULL;
	result->height = 0;
	result->width = 0;
	return (result);
}
