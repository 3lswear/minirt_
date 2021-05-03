#include "minirt.h"

t_color	parse_color(char *string, int lc)
{
	t_color	result;
	char	**data;
	int		r;
	int		g;
	int		b;

	data = ft_split(string, ',');
	if (split_len(data) != 3)
		handle_error(ERR_TOKENS, lc);
	r = ft_atoi(data[0]);
	g = ft_atoi(data[1]);
	b = ft_atoi(data[2]);
	if ((r > 255 || r < 0)
		|| (g > 255 || g < 0)
		|| (b > 255 || b < 0))
		handle_error(ERR_COLOR, lc);
	result = new_color(r, g, b);
	liberator(data);
	return (result);
}

double	parse_onlypos(char *string, int lc)
{
	double	result;

	result = parse_flpos(string, lc);
	if (result == 0)
		handle_error(ERR_NEG, lc);
	return (result);
}
