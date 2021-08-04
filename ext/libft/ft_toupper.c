#include "libft.h"

int	ft_toupper(int c)
{
	if ((ft_isalpha(c)) && (c >= 'a'))
		return (c + ('A' - 'a'));
	return (c);
}
