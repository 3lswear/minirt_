#include "minirt.h"

void	lst_cams(t_scene *scene, char **data, t_parse *pa)
{
	t_cam	*cam;

	if (split_len(data) != 4)
		handle_error(ERR_TOKENS, pa->lc);
	cam = new_cam(
			parse_point(data[1], pa->lc),
			parse_norm(data[2], pa->lc),
			parse_flpos(data[3], pa->lc)
			);
	ft_lstadd_back(&(scene->cams), ft_lstnew(cam));
	printf("cam->origin %lf %lf %lf\n", cam->origin->x, cam->origin->y,
		cam->origin->z);
	print_str_array(data);
}

void	parse_objects(t_scene *scene, char **data, t_parse *pa)
{
	char	*id;

	id = data[0];
	if (!ft_strncmp(id, "sp", ft_strlen(id)))
		lst_spheres(scene, data, pa);
	else if (!ft_strncmp(id, "pl", ft_strlen(id)))
		lst_planes(scene, data, pa);
	else if (!ft_strncmp(id, "sq", ft_strlen(id)))
		lst_squares(scene, data, pa);
	else if (!ft_strncmp(id, "tr", ft_strlen(id)))
		lst_triangs(scene, data, pa);
	else if (!ft_strncmp(id, "cy", ft_strlen(id)))
		lst_cylinds(scene, data, pa);
}

void	parse_lights(t_scene *scene, char **data, t_parse *pa)
{
	t_light	*light;

	if (split_len(data) != 4)
		handle_error(ERR_TOKENS, pa->lc);
	light = l_new(
			parse_point(data[1], pa->lc),
			parse_flpos(data[2], pa->lc),
			parse_color(data[3], pa->lc)
			);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}

void	parse_ambient(t_scene *scene, char **data, t_parse *pa)
{
	pa->amb_count++;
	if (split_len(data) != 3)
		handle_error(ERR_TOKENS, pa->lc);
	scene->amb_intensity = parse_flpos(data[1], pa->lc);
	scene->ambient = parse_color(data[2], pa->lc);
}
