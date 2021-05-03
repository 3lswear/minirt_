#include "minirt.h"

void 	parse_redirector(t_scene **scene, char **data, t_parse *pa)
{
	if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
		parse_res(data, *scene, pa);
	else if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
		parse_ambient(*scene, data, pa);
	else if (!ft_strncmp(data[0], "c", ft_strlen(data[0])))
		lst_cams(*scene, data, pa);
	else if (!ft_strncmp(data[0], "l", ft_strlen(data[0])))
		parse_lights(*scene, data, pa);
	else
		parse_objects(*scene, data, pa);
}

void	parse_input(char *file, t_scene **scene, t_win *window)
{
	int		fd;
	char	*line;
	char	**data;
	t_parse	parse;

	fd = open(file, O_RDONLY);
	(void)window;
	*scene = new_scene(NULL);
	(*scene)->lights = NULL;
	(*scene)->objects = NULL;
	parse.lc = 1;
	parse.res_count = 0;
	parse.amb_count = 0;
	while (1)
	{
		parse.ret = get_next_line(fd, &line);
		if (parse.ret != 1)
			break ;
		if (!ft_strlen(line))
		{
			free(line);
			parse.lc++;
			continue ;
		}
		data = split_ws(line);
		parse_redirector(scene, data, &parse);
		free(line);
		liberator(data);
		parse.lc++;
	}
	if (!parse.ret)
		free(line);
	if (parse.ret == -1)
		handle_error(ERR_FILE, -1);
	close(fd);
}
