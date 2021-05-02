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
	result = new_color(
		ft_atoi(data[0]),
		ft_atoi(data[1]),
		ft_atoi(data[2])
	);
	/* result = argb_color( */
	/* 	ft_atoi(data[0]), */
	/* 	ft_atoi(data[1]), */
	/* 	ft_atoi(data[2]) */
	liberator(data);
	
	return (result);
}

void print_vec(t_vec *vec, char *label)
{
	printf("%s => %lf %lf %lf\n", label, vec->x, vec->y, vec->z);
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
	t_obj *object;

	sphere = new_sphere(
			parse_point(data[1]),
			parse_doubles(data[2])
			);
	sphere.color = parse_color(data[3]);
	object = new_object(T_SPHERE, NULL);
	object->obj.sphere = sphere;
	object->color = sphere.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void lst_planes(t_scene *scene, char **data)
{
	t_plane plane;
	t_obj *object;

	plane = new_plane(
			parse_point(data[1]),
			parse_vec(data[2]),
			/* parse_norm(data[2]), */
			parse_color(data[3])
	);
	/* maybe remove */
	v_norm_inplace(plane.norm);
	object = new_object(T_PLANE, NULL);
	object->obj.plane = plane;
	object->color = plane.color;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void lst_squares(t_scene *scene, char **data)
{
	t_obj *object;

	object = new_object(T_SQUARE, NULL);
	object->obj.square = new_square(
		parse_point(data[1]),
		/* parse_norm(data[2]), */
		parse_vec(data[2]),
		parse_flpos(data[3]),
		parse_color(data[4])
	);
	v_norm_inplace(object->obj.square.norm);
	sq_get_vertices(&object->obj.square);
	object->color = object->obj.square.color;
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
	object->color = object->obj.triang.color;
	object->obj.triang.norm = triang_get_norm(&object->obj.triang);
	/* printf("tri color => %X\n", object->obj.triang.color); */
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void lst_cams(t_scene *scene, char **data)
{
	t_cam *cam;
	cam = new_cam(
		parse_point(data[1]),
		/* parse_norm(data[2]), */
		parse_vec(data[2]),
		parse_flpos(data[3])
	);
	ft_lstadd_back(&(scene->cams), ft_lstnew(cam));
	printf("cam->origin %lf %lf %lf\n", cam->origin->x, cam->origin->y, cam->origin->z);
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
	
	light = l_new(
				parse_point(data[1]),
				parse_flpos(data[2]),
				parse_color(data[3])
	);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}

void parse_ambient(t_scene *scene, char **data)
{
	scene->amb_intensity = parse_flpos(data[1]);
	scene->ambient = parse_color(data[2]);
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
