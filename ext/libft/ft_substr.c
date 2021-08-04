#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	result = (char *)ft_calloc((len + 1), sizeof(char));
	if (!len && result)
		return (result);
	else if (result)
		ft_memcpy(result, (char *)&s[start], len);
	return (result);
}
