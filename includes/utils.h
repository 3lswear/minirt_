#ifndef UTILS_H
# define UTILS_H

double idiv(int a, int b);
void handle_error(int value);
void parse_input(char *file, t_scene **scene, t_win *window);
void	parse_res(char **line, t_scene *scene);

int	iswhitespace(const char *chr);
char	**split_ws(char const *s);
void	*liberator(char **array);
char	*strchr_ws(const char *s);

double	ft_strtof(const char *str);
void print_vec(t_vec *vec, char *label);
void graceful_exit(t_win *win, t_scene *scene);

#endif
