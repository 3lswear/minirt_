#include "minirt.h"

void	parse_res(char **line, t_scene *scene, t_win *win)
{
	(void)win;
	scene->width = ft_atoi(line[1]);
	scene->height = ft_atoi(line[2]);
	if (scene->width > W_MAX)
		scene->width = W_MAX;
	if (scene->height > H_MAX)
		scene->height = H_MAX;
}
