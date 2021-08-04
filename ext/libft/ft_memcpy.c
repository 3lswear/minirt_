#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	return (ft_memcpy_bd(dest, src, n, 0));
}
