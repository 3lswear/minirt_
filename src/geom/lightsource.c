#include "minirt.h"

t_light	*l_new(t_vec *coords, double brightess, t_color color)
{
	t_light	*light;

	light = ft_calloc(sizeof(t_light), 1);
	if (!light)
		handle_error(-1);
	light->coords = coords;
	light->brightess = brightess;
	light->color = color;
	return (light);
}
