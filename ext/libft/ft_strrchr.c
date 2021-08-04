#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	return (ft_strchr_bd(s, c, 1));
}
