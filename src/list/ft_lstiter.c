#include "minirt.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		handle_error(ERR_LIST, -1);
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}
