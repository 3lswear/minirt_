#include "libft.h"
#define FT_INT_MAX 2147483647

static int	ft_iswhitespace(const char *chr)
{
	if (*chr == '\n' || *chr == '\v' || *chr == '\f'
		|| *chr == '\r' || *chr == ' ' || *chr == '\t')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	is_negative;
	int	result;

	result = 0;
	is_negative = 0;
	while (ft_iswhitespace(str))
		str++;
	if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if ((result > FT_INT_MAX / 10))
			return ((result = is_negative - 1));
		result = result * 10 + (*str - '0');
		str++;
	}
	if (is_negative)
		result = -result;
	return (result);
}
