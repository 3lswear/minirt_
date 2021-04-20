#include "minirt.h"

void	parse_res(char **line, t_scene *scene)
{
	scene->width = ft_atoi(line[1]);
	scene->height = ft_atoi(line[2]);

}
