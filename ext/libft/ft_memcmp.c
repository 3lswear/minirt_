#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				retval;
	unsigned int	count;

	count = 0;
	retval = 0;
	while (count++ < n)
	{
		retval = ((unsigned char *)s1)[count - 1] - ((unsigned char *)s2)
		[count - 1];
		if (retval)
			return (retval);
	}
	return (retval);
}
