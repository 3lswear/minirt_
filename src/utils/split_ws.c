#include "minirt.h"


static unsigned int	get_wc(const char *s)
{
	unsigned int	count;

	count = 0;
	while (*s)
	{
		if (iswhitespace(s))
			s++;
		else
		{
			count++;
			while (*s && !iswhitespace(s))
				s++;
		}
	}
	return (count);
}

static void	*liberator(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char 	**checks(const char *s)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc((get_wc(s) + 1), sizeof(char *));
	return (result);
}

char	**split_ws(char const *s)
{
	char			**result;
	unsigned int	wc;
	unsigned int	j;
	int				len;

	result = checks(s);
	if (!result)
		return (result);
	j = 0;
	wc = get_wc(s);
	while (j < wc)
	{
		while (iswhitespace(s))
			s++;
		len = strchr_ws(s) - s;
		if (len < 0)
			len = ft_strlen(s);
		result[j++] = ft_substr(s, 0, len);
		if (!result[j - 1])
			return (liberator(result));
		while (!iswhitespace(s) && *s)
			s++;
	}
	result[wc] = NULL;
	return (result);
}
