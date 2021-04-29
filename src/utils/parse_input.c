#include "minirt.h"

t_point *parse_point(char *string)
{
	t_vec *result;
	char **data;

	data = ft_split(string, ',');
	result = v_new(
		ft_strtof(data[0]),
		ft_strtof(data[1]),
		ft_strtof(data[2])
	);
	liberator(data);
	return (result);
}

t_vec *parse_vec(char *string)
{
	return(parse_point(string));
}

t_vec *parse_norm(char *string)
{
	t_vec *vec;

	vec = parse_vec(string);
	if (v_len(vec) != 1)
	{
		free(vec);
		handle_error(ERR_SUBNORM);
	}
	return (vec);
}

double parse_doubles(char *string)
{
	double result;

	result = ft_strtof(string);
	return (result);
}

double parse_flpos(char *string)
{
	double result;

	result = parse_doubles(string);
	if (result < 0)
		handle_error(ERR_NEG);
	return (result);
}

t_color parse_color(char *string)
{
	t_color result;
	char **data;

	/* check rgb values */
	data = ft_split(string, ',');
	result = argb_color(
		ft_atoi(data[0]),
		ft_atoi(data[1]),
		ft_atoi(data[2])
	);
	liberator(data);
	
	return (result);
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

t_obj *new_object(int type, t_object *object)
{
	t_obj *result;

	(void)object;
	result = malloc(sizeof(t_obj));
	result->type = type;

	return(result);
}

void lst_spheres(t_scene *scene, char **data)
{
	t_sphere sphere;
	char **vec;
	char **color;
	t_obj *object;

	vec = ft_split(data[1], ',');
	sphere = new_sphere(
			v_new(ft_strtof(vec[0]),
				ft_strtof(vec[1]),
				ft_strtof(vec[2])),
			ft_strtof(data[2]));
	color = ft_split(data[3], ',');
	sphere.color = argb_color(
		ft_atoi(color[0]),
		ft_atoi(color[1]),
		ft_atoi(color[2]));
	object = new_object(T_SPHERE, NULL);
	object->obj.sphere = sphere;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
	liberator(vec);
	liberator(color);
}

void lst_planes(t_scene *scene, char **data)
{
	t_plane plane;
	char **pos;
	char **norm;
	char **color;
	t_obj *object;

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
	plane.color = argb_color(
			ft_atoi(color[0]),
			ft_atoi(color[1]),
			ft_atoi(color[2])
		);
	/* maybe remove */
	v_norm(plane.norm);
	object = new_object(T_PLANE, NULL);
	object->obj.plane = plane;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
	liberator(pos);
	liberator(norm);
	liberator(color);
}

void lst_squares(t_scene *scene, char **data)
{
	t_obj *object;

	object = new_object(T_SQUARE, NULL);
	object->obj.square = new_square(
		parse_point(data[1]),
		parse_norm(data[2]),
		parse_flpos(data[3]),
		parse_color(data[4])
	);
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void lst_triangs(t_scene *scene, char **data)
{
	t_obj *object;

	object = new_object(T_TRIANG, NULL);
	object->obj.triang = new_triang(
		parse_point(data[1]),
		parse_point(data[2]),
		parse_point(data[3]),
		parse_color(data[4])
	);
	object->obj.triang.norm = triang_get_norm(&object->obj.triang);
	printf("tri color => %X\n", object->obj.triang.color);
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void lst_cams(t_scene *scene, char **data)
{
	t_cam *cam;
	cam = new_cam(
		parse_point(data[1]),
		parse_norm(data[2]),
		ft_strtof(data[3])
	);
	ft_lstadd_back(&(scene->cams), ft_lstnew(cam));
	print_str_array(data);
}

void parse_objects(t_scene *scene, char **data)
{
	char *id;
	id = data[0];
	if (!ft_strncmp(id, "sp", ft_strlen(id)))
		lst_spheres(scene, data);
	else if (!ft_strncmp(id, "pl", ft_strlen(id)))
		lst_planes(scene, data);
	else if (!ft_strncmp(id, "sq", ft_strlen(id)))
		lst_squares(scene, data);
	else if (!ft_strncmp(id, "tr", ft_strlen(id)))
		lst_triangs(scene, data);

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
	*scene = new_scene(NULL);
	(*scene)->lights = NULL;
	(*scene)->objects = NULL;

	/* light = l_new(v_new(3, 0, -3), 0.9, WHITE); */
	/* (*scene)->light = light; */

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		if (!ft_strlen(line))
			continue;
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
