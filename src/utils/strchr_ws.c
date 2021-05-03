#include "minirt.h"

int	iswhitespace(const char *chr)
{
	if (*chr == '\n' || *chr == '\v' || *chr == '\f'
		|| *chr == '\r' || *chr == ' ' || *chr == '\t')
		return (1);
	return (0);
}

char	*strchr_ws(const char *s)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (iswhitespace(&s[i]))
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}
