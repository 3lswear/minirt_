#ifndef UTILS_H
# define UTILS_H

typedef struct s_parse
{
	int	res_count;
	int amb_count;
	int valid;
	int	lc;
	int	ret;
	
}	t_parse;

double	idiv(int a, int b);
void	handle_error(int value, int line);
void	parse_input(char *file, t_scene **scene, t_win *window);
void	parse_res(char **line, t_scene *scene, t_parse *pa);
int	split_len(char **data);

t_point	*parse_point(char *string, int lc);
t_vec	*parse_vec(char *string, int lc);
t_vec	*parse_norm(char *string, int lc);
double	parse_doubles(char *string, int lc);
double	parse_flpos(char *string, int lc);
t_color	parse_color(char *string, int lc);

void	lst_cams(t_scene *scene, char **data, t_parse *pa);
void	parse_objects(t_scene *scene, char **data, t_parse *pa);
void	parse_lights(t_scene *scene, char **data, t_parse *pa);
void	parse_ambient(t_scene *scene, char **data, t_parse *pa);

void	lst_spheres(t_scene *scene, char **data, t_parse *pa);
void	lst_planes(t_scene *scene, char **data, t_parse *pa);
void	lst_squares(t_scene *scene, char **data, t_parse *pa);
void	lst_triangs(t_scene *scene, char **data, t_parse *pa);
void	lst_cylinds(t_scene *scene, char **data, t_parse *pa);

int		free4(void *a, void *b, void *c, void *d);

int		iswhitespace(const char *chr);
char	**split_ws(char const *s);
void	*liberator(char **array);
char	*strchr_ws(const char *s);

double	ft_strtof(const char *str);
void	print_vec(t_vec *vec, char *label);
void	graceful_exit(t_win *win, t_scene *scene, int save_arg);
void	exit_by_close(t_win *win, t_scene *scene);

void	write_file(t_win *win, t_scene *scene, int fd);
void	save_screen(t_win *win, t_scene *scene);

void	free_sphere(t_obj *obj);
void	free_plane(t_obj *obj);
void	free_triang(t_obj *obj);
void	free_square(t_obj *obj);
void	free_cylind(t_obj *obj);

void	print_vec(t_vec *vec, char *label);
void	lst_print(t_list *lst);
void	print_str_array(char **data);
void	obj_lst_print(t_list *lst);

#endif
