#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return (ft_memcpy_bd(dest, src, n, 1));
	else if (src > dest)
		return (ft_memcpy_bd(dest, src, n, 0));
	else
		return (dest);
}
