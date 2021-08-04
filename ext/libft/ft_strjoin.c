#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result)
	{
		ft_strlcpy(result, (char *)s1, ft_strlen(s1) + 1);
		ft_strlcat(result, (char *)s2, len + 1);
	}
	return (result);
}
