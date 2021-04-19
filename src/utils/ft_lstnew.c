#include "minirt.h"

t_list *ft_lstnew(void *data)
{
	t_list *result;

	result = ft_calloc(1, sizeof(t_list));
	if (!result)
		handle_error(-1);
	result->data = data;
	result->next = NULL;
	return (result);
}
