#include "minirt.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		handle_error(ERR_LIST);
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}
