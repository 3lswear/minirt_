#include "minirt.h"

t_point	*parse_point(char *string)
{
	t_vec	*result;
	char	**data;

	data = ft_split(string, ',');
	result = v_new(
			ft_strtof(data[0]),
			ft_strtof(data[1]),
			ft_strtof(data[2])
			);
	liberator(data);
	return (result);
}

t_vec	*parse_vec(char *string)
{
	return (parse_point(string));
}

t_vec	*parse_norm(char *string)
{
	t_vec	*vec;

	vec = parse_vec(string);
	/* attention!!! */
	if (vec->x > 1 || vec->x < -1 ||
		vec->y > 1 || vec->y < -1 ||
		vec->z > 1 || vec->z < -1)
	{
		free(vec);
		handle_error(ERR_SUBNORM);
	}
	v_norm_inplace(vec);
	return (vec);
}

double	parse_doubles(char *string)
{
	double	result;

	result = ft_strtof(string);
	return (result);
}

double	parse_flpos(char *string)
{
	double	result;

	result = parse_doubles(string);
	if (result < 0)
		handle_error(ERR_NEG);
	return (result);
}