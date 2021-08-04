#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_size;
	size_t	i;

	n_size = ft_strlen(needle);
	if (!n_size)
		return ((char *)haystack);
	if (n_size > len && haystack)
		return (NULL);
	i = 0;
	while ((i <= len - n_size) && (haystack[i]))
	{
		if (!ft_strncmp(needle, &haystack[i], n_size))
			return ((char *)&(haystack)[i]);
		i++;
	}
	return (NULL);
}
