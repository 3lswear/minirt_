#ifndef UTILS_H
# define UTILS_H

double	idiv(int a, int b);
void	handle_error(int value);
void	parse_input(char *file, t_scene **scene, t_win *window);
void	parse_res(char **line, t_scene *scene);

int		free4(void *a, void *b, void *c, void *d);

int		iswhitespace(const char *chr);
char	**split_ws(char const *s);
void	*liberator(char **array);
char	*strchr_ws(const char *s);

double	ft_strtof(const char *str);
void	print_vec(t_vec *vec, char *label);
void	graceful_exit(t_win *win, t_scene *scene);
void	exit_by_close(t_win *win, t_scene *scene);

void write_file(t_win *win, t_scene *scene, int fd);
void save_screen(t_win *win, t_scene *scene);

#endif
