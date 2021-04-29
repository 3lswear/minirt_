#include "minirt.h"

#define FT_INT_MAX 2147483647

static int	ft_iswhitespace(const char *chr)
{
	if (*chr == '\n' || *chr == '\v' || *chr == '\f'
		|| *chr == '\r' || *chr == ' ' || *chr == '\t')
		return (1);
	return (0);
}

double	ft_strtof(const char *str)
{
	int			sign;
	double		result;
	const char	*dot;

	result = 0;
	sign = 1;
	while (ft_iswhitespace(str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
	{
		dot = str;
		while (ft_isdigit(*++str))
			result = result + idiv((*str - '0'), pow(10, str - dot));
	}
	return (result * sign);
}
