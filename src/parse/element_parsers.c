#include "minirt.h"

void	lst_cams(t_scene *scene, char **data)
{
	t_cam	*cam;

	cam = new_cam(
			parse_point(data[1]),
			parse_vec(data[2]),
			parse_flpos(data[3])
			);
	ft_lstadd_back(&(scene->cams), ft_lstnew(cam));
	printf("cam->origin %lf %lf %lf\n", cam->origin->x, cam->origin->y,
		cam->origin->z);
	print_str_array(data);
}

void	parse_objects(t_scene *scene, char **data)
{
	char	*id;

	id = data[0];
	if (!ft_strncmp(id, "sp", ft_strlen(id)))
		lst_spheres(scene, data);
	else if (!ft_strncmp(id, "pl", ft_strlen(id)))
		lst_planes(scene, data);
	else if (!ft_strncmp(id, "sq", ft_strlen(id)))
		lst_squares(scene, data);
	else if (!ft_strncmp(id, "tr", ft_strlen(id)))
		lst_triangs(scene, data);
	else if (!ft_strncmp(id, "cy", ft_strlen(id)))
		lst_cylinds(scene, data);
}

void	parse_lights(t_scene *scene, char **data)
{
	t_light	*light;

	light = l_new(
			parse_point(data[1]),
			parse_flpos(data[2]),
			parse_color(data[3])
			);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}

void	parse_ambient(t_scene *scene, char **data)
{
	scene->amb_intensity = parse_flpos(data[1]);
	scene->ambient = parse_color(data[2]);
}