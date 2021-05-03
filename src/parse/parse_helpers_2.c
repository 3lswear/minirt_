#include "minirt.h"

t_color	parse_color(char *string)
{
	t_color	result;
	char	**data;

	/* check rgb values */
	data = ft_split(string, ',');
	result = new_color(
			ft_atoi(data[0]),
			ft_atoi(data[1]),
			ft_atoi(data[2])
			);
	liberator(data);
	return (result);
}