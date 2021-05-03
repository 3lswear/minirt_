#include "minirt.h"

t_point	*parse_point(char *string, int lc)
{
	t_vec	*result;
	char	**data;

	data = ft_split(string, ',');
	if (split_len(data) != 3)
		handle_error(ERR_TOKENS, lc);
	result = v_new(
			ft_strtof(data[0]),
			ft_strtof(data[1]),
			ft_strtof(data[2])
			);
	liberator(data);
	return (result);
}

t_vec	*parse_vec(char *string, int lc)
{
	t_vec	*result;

	result = parse_point(string, lc);
	if (v_len(result) < FLT_EPSILON)
		handle_error(ERR_SUBNORM, lc);
	return (result);
}

t_vec	*parse_norm(char *string, int lc)
{
	t_vec	*vec;

	vec = parse_vec(string, lc);
	if (vec->x > 1 || vec->x < -1
		|| vec->y > 1 || vec->y < -1
		|| vec->z > 1 || vec->z < -1)
	{
		free(vec);
		handle_error(ERR_SUBNORM, lc);
	}
	v_norm_inplace(vec);
	return (vec);
}

double	parse_doubles(char *string, int lc)
{
	double	result;

	(void)lc;
	result = ft_strtof(string);
	return (result);
}

double	parse_flpos(char *string, int lc)
{
	double	result;

	result = parse_doubles(string, lc);
	if (result < 0)
		handle_error(ERR_NEG, lc);
	return (result);
}
