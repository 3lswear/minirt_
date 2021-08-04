#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s)
		return (NULL);
	result = ft_strdup(s);
	i = 0;
	if (result && f)
	{
		while (result[i])
		{
			result[i] = (f)(i, result[i]);
			i++;
		}
	}
	else
		return (NULL);
	return (result);
}
