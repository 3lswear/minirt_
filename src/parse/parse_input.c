#include "minirt.h"

void 	parse_redirector(t_scene **scene, char **data, t_win *win)
{
	if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
		parse_res(data, *scene, win);
	else if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
		parse_ambient(*scene, data);
	else if (!ft_strncmp(data[0], "c", ft_strlen(data[0])))
		lst_cams(*scene, data);
	else if (!ft_strncmp(data[0], "l", ft_strlen(data[0])))
		parse_lights(*scene, data);
	else if (data[0][0] == '#')
		print_str_array(data);
	else
		parse_objects(*scene, data);
}

void	parse_input(char *file, t_scene **scene, t_win *window)
{
	int		fd;
	char	*line;
	int		ret;
	char	**data;
	int		lc;
	struct	s_parse parse;

	fd = open(file, O_RDONLY);
	(void)window;
	(void)parse;
	/* scene initialization */
	*scene = new_scene(NULL);
	(*scene)->lights = NULL;
	(*scene)->objects = NULL;
	lc = 1;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		if (!ft_strlen(line))
		{
			free(line);
			continue;
		}
		data = split_ws(line);
		parse_redirector(scene, data, window);
		/* printf("line from gnl => %s\n", line); */
		free(line);
		liberator(data);
	}
	if (!ret)
		free(line);
	if (ret == -1)
		handle_error(ERR_FILE, -1);
	close(fd);
}