#include "minirt.h"

void ft_putstr(void *str)
{
	ft_putstr_fd((char *)str, 1);
}

void lst_print(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->data, 1);
		ft_putstr_fd(" -> ", 1);
		lst = lst->next;
	}
	ft_putendl_fd("", 1);

}

void parse_input(char *file, t_scene *scene, t_win *window)
{
	int fd;
	char *line;
	char *temp;
	int ret;
	char **data;
	const char *whitespace;

	whitespace = " \v\f\r\t";
	fd = open(file, O_RDONLY);
	(void)window;

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		printf("line from gnl => %s\n", line);
		temp = line;
		line = ft_strtrim(line, whitespace);
		free(temp);
		data = split_ws(line);
		if (!ft_strncmp(data[0], "R", 2))
			parse_res(data, scene);

		int splt_i = 0;
		while (data[splt_i])
		{
			printf("[%s]\n", data[splt_i]);
			splt_i++;
		}

		free(line);
	}
	if (!ret)
		free(line);

	close(fd);
}
