#ifndef UTILS_H
# define UTILS_H

float idiv(int a, int b);
void handle_error(int value);
void parse_input(char *file, t_scene **scene, t_win *window);
void	parse_res(char **line, t_scene *scene);

int	iswhitespace(const char *chr);
char	**split_ws(char const *s);
char	*strchr_ws(const char *s);

float	ft_strtof(const char *str);
#endif
