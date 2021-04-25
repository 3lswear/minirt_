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
	char **color;

	vec = ft_split(data[1], ',');
	sphere = new_sphere(
			v_new(ft_strtof(vec[0]),
				ft_strtof(vec[1]),
				ft_strtof(vec[2])),
			ft_strtof(data[2]));
	color = ft_split(data[3], ',');
	sphere->color = argb_color(
		ft_atoi(color[0]),
		ft_atoi(color[1]),
		ft_atoi(color[2]));
	ft_lstadd_back(&(scene->spheres), ft_lstnew(sphere));
	liberator(vec);
	liberator(color);
}

void lst_planes(t_scene *scene, char **data)
{
	t_plane *plane;
	char **pos;
	char **norm;
	char **color;

	pos = ft_split(data[1], ',');
	norm = ft_split(data[2], ',');
	plane = new_plane(
		v_new(
			ft_strtof(pos[0]),
			ft_strtof(pos[1]),
			ft_strtof(pos[2])
		),
		v_new(
			ft_strtof(norm[0]),
			ft_strtof(norm[1]),
			ft_strtof(norm[2])
		)
	);
	color = ft_split(data[3], ',');
	plane->color = argb_color(
			ft_atoi(color[0]),
			ft_atoi(color[1]),
			ft_atoi(color[2])
		);
	ft_lstadd_back(&(scene->planes), ft_lstnew(plane));
	liberator(pos);
	liberator(norm);
	liberator(color);
}

void parse_objects(t_scene *scene, char **data)
{
	char *id;
	id = data[0];
	if (!ft_strncmp(id, "sp", ft_strlen(id)))
		lst_spheres(scene, data);
	else if (!ft_strncmp(id, "pl", ft_strlen(id)))
		lst_planes(scene, data);

}

void parse_lights(t_scene *scene, char **data)
{
	t_light *light;
	char **pos;
	char **color;
	
	pos = ft_split(data[1], ',');
	color = ft_split(data[3], ',');
	light = l_new(
				v_new(
					ft_strtof(pos[0]),
					ft_strtof(pos[1]),
					ft_strtof(pos[2])),
				ft_strtof(data[2]),
				argb_color(
					ft_atoi(color[0]),
					ft_atoi(color[1]),
					ft_atoi(color[2])));
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
	liberator(pos);
	liberator(color);
}

void parse_ambient(t_scene *scene, char **data)
{
	char **split;

	split = ft_split(data[2], ',');
	scene->amb_intensity = ft_strtof(data[1]);
	scene->ambient = argb_color(
				ft_atoi(split[0]),
				ft_atoi(split[1]),
				ft_atoi(split[2]));
	liberator(split);
}

void parse_input(char *file, t_scene **scene, t_win *window)
{
	int fd;
	char *line;
	int ret;
	char **data;

	fd = open(file, O_RDONLY);
	(void)window;

	/* scene initialization */
	t_cam *cam;

	cam = new_cam(v_new(0, 0, 0), v_new(0, 0, -1), 90);
	*scene = new_scene(cam);
	(*scene)->spheres = NULL;
	(*scene)->lights = NULL;

	/* light = l_new(v_new(3, 0, -3), 0.9, WHITE); */
	/* (*scene)->light = light; */

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		/* printf("line from gnl => %s\n", line); */
		data = split_ws(line);
		if (!ft_strncmp(data[0], "R", ft_strlen(data[0])))
			parse_res(data, *scene);
		/* move to separate func */
		else if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
			parse_ambient(*scene, data);
		else if (!ft_strncmp(data[0], "c", ft_strlen(data[0])))
			print_str_array(data);
		else if (!ft_strncmp(data[0], "l", ft_strlen(data[0])))
			parse_lights(*scene, data);
		else if (data[0][0] == '#')
			print_str_array(data);
		else
			parse_objects(*scene, data);
			/* ft_lstadd_back(&obj_list, ft_lstnew(data)); */
		free(line);
		liberator(data);
	}
	if (!ret)
		free(line);
	close(fd);

	/* (*scene)->objs = obj_list; */
	printf("scene->width = %f\n", (*scene)->width);
	printf("scene->height = %f\n", (*scene)->height);
	/* obj_lst_print(obj_list); */
}
