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

void print_str_array(char **data)
{
	int i;

	i = 0;
	while (data[i])
	{
		printf("[%s]\t", data[i]);
		i++;
	}
	printf("\n");
}

void obj_lst_print(t_list *lst)
{
	printf("   ");
	while (lst)
	{
		print_str_array(lst->data);
		printf("-> ");
		lst = lst->next;
	}
	printf("NULL\n");
}

void parse_input(char *file, t_scene **scene, t_win *window)
{
	int fd;
	char *line;
	char *temp;
	int ret;
	char **data;
	const char *whitespace;
	t_list *obj;
	t_list *obj_list = NULL;

	whitespace = " \v\f\r\t";
	fd = open(file, O_RDONLY);
	(void)window;

	/* scene initialization */
	t_cam *cam;
	t_sphere *sph;

	sph = new_sphere(v_new(3, 2, -20), 4);

	cam = new_cam(v_new(0, 0, 0), v_new(0, 0, -1), 90);
	*scene = new_scene(cam, obj_list);

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		/* printf("line from gnl => %s\n", line); */
		temp = line;
		line = ft_strtrim(line, whitespace);
		free(temp);
		data = split_ws(line);
		if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
			parse_res(data, *scene);
		else if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
			print_str_array(data);
		else if (!ft_strncmp(data[0], "c", ft_strlen(data[0])))
			print_str_array(data);
		else if (data[0][0] == '#')
			print_str_array(data);
		else
		{
			obj = ft_lstnew(data);
			ft_lstadd_back(&obj_list, obj);
		}

		/* free(line); */
	}
	(*scene)->objs = obj_list;
	printf("scene->width = %f\n", (*scene)->width);
	printf("scene->height = %f\n", (*scene)->width);
	/* print_str_array(obj_list->data); */
	obj_lst_print(obj_list);
	if (!ret)
		free(line);

	close(fd);
}
