#include "minirt.h"

size_t	ft_lstsize(t_list *list)
{
	size_t	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}
