#include "libft.h"

static int	ft_issep(const char *s, char sep)
{
	if (*s == sep)
		return (1);
	else
		return (0);
}

static unsigned int	get_wc(const char *s, char sep)
{
	unsigned int	count;

	count = 0;
	while (*s)
	{
		if (ft_issep(s, sep))
			s++;
		else
		{
			count++;
			while (*s && !ft_issep(s, sep))
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

char 	**checks(const char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc((get_wc(s, c) + 1), sizeof(char *));
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	wc;
	unsigned int	j;
	int				len;

	result = checks(s, c);
	if (!result)
		return (result);
	j = 0;
	wc = get_wc(s, c);
	while (j < wc)
	{
		while (ft_issep(s, c))
			s++;
		len = ft_strchr(s, c) - s;
		if (len < 0)
			len = ft_strlen(s);
		result[j++] = ft_substr(s, 0, len);
		if (!result[j - 1])
			return (liberator(result));
		while (!ft_issep(s, c) && *s)
			s++;
	}
	result[wc] = NULL;
	return (result);
}
