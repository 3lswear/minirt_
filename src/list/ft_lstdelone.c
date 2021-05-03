#include "minirt.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		handle_error(ERR_LIST, -1);
	del(lst->data);
	free(lst);
}
