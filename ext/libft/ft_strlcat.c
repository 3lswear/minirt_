#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	result;

	i = ft_strlen(dest);
	if (ft_strlen(dest) < size)
		result = i + ft_strlen(src);
	else
		result = size + ft_strlen(src);
	while ((i < size - 1) && (*src) && (size > 0))
		dest[i++] = *(src++);
	dest[i] = 0;
	return (result);
}
