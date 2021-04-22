#include "minirt.h"

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

void lst_spheres(t_scene *scene, char **data)
{
	t_sphere *sphere;
	char **vec;
	char **center;

	vec = ft_split(data[1], ',');
	sphere = new_sphere(
			v_new(ft_strtof(vec[0]),
				ft_strtof(vec[1]),
				ft_strtof(vec[2])),
			ft_strtof(data[2]));
	center = ft_split(data[3], ',');
	sphere->color = argb_color(
		ft_atoi(center[0]),
		ft_atoi(center[1]),
		ft_atoi(center[2]));
	ft_lstadd_back(&(scene->spheres), ft_lstnew(sphere));
}

void parse_objects(t_scene *scene, char **data)
{
	char *id;
	id = data[0];
	if (!ft_strncmp(id, "sp", ft_strlen(id)))
		lst_spheres(scene, data);

}

void parse_input(char *file, t_scene **scene, t_win *window)
{
	int fd;
	char *line;
	int ret;
	char **data;
	char **split;
	float amb_mult;
	t_list *obj_list = NULL;

	// const char *whitespace;
	// whitespace = " \v\f\r\t";
	fd = open(file, O_RDONLY);
	(void)window;

	/* scene initialization */
	t_cam *cam;

	cam = new_cam(v_new(0, 0, 0), v_new(0, 0, -1), 90);
	*scene = new_scene(cam, obj_list);
	(*scene)->spheres = NULL;
	printf("obj_list => %p\n", obj_list);
	printf("scene->spheres => %p\n", (*scene)->spheres);

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		/* printf("line from gnl => %s\n", line); */
		data = split_ws(line);
		if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
			parse_res(data, *scene);
		else if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
		{
			split = ft_split(data[2], ',');
			amb_mult = ft_strtof(data[1]);
			(*scene)->ambient = argb_color(
						ft_atoi(split[0]) * amb_mult,
						ft_atoi(split[1]) * amb_mult,
						ft_atoi(split[2]) * amb_mult);
			free(split);
		}
			/* print_str_array(data); */
		else if (!ft_strncmp(data[0], "c", ft_strlen(data[0])))
			print_str_array(data);
		else if (data[0][0] == '#')
			print_str_array(data);
		else
			parse_objects(*scene, data);
			/* ft_lstadd_back(&obj_list, ft_lstnew(data)); */
		/* free(line); */
	}

	(*scene)->objs = obj_list;
	printf("scene->width = %f\n", (*scene)->width);
	printf("scene->height = %f\n", (*scene)->height);
	obj_lst_print(obj_list);
	if (!ret)
		free(line);
	close(fd);
}
