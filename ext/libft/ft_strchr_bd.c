#include "libft.h"

char	*ft_strchr_bd(const char *s, int c, int dir)
{
	char	*retval;
	size_t	i;
	size_t	len;

	retval = NULL;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((unsigned char)c == s[i])
			retval = (char *)&s[i];
		if ((dir == 0) && (retval))
			return (retval);
		i++;
	}
	return (retval);
}
