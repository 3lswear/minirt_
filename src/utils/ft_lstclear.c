#include "minirt.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	if (!head)
		handle_error(ERR_LIST);
	ft_lstiter(*head, del);
	*head = NULL;
}
