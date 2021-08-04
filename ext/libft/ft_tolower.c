#include "libft.h"

int	ft_tolower(int c)
{
	if ((ft_isalpha(c)) && (c <= 'Z'))
		return (c + ('a' - 'A'));
	return (c);
}
