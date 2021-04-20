#include "minirt.h"

t_scene *new_scene(t_cam *cam, t_list *obj_list)
{
	t_scene *result;

	result = malloc(sizeof(t_scene));
	if (!result)
		handle_error(-1);
	result->cams = cam;
	result->objs = obj_list;
	result->height = 0;
	result->width = 0;
	return (result);
}
