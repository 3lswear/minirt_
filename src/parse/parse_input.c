#include "minirt.h"


void	parse_input(char *file, t_scene **scene, t_win *window)
{
	int		fd;
	char	*line;
	int		ret;
	char	**data;

	fd = open(file, O_RDONLY);
	(void)window;
	/* scene initialization */
	*scene = new_scene(NULL);
	(*scene)->lights = NULL;
	(*scene)->objects = NULL;
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
		/* printf("line from gnl => %s\n", line); */
		data = split_ws(line);
		if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
			parse_res(data, *scene);
		/* move to separate func */
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
		free(line);
		liberator(data);
	}
	if (!ret || ret == -1)
		free(line);
	close(fd);
}