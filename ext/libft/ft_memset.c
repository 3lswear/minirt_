#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*dest;

	if (n)
		dest = s;
	while (n > 0)
	{
		*dest++ = c;
		n--;
	}
	return (s);
}
