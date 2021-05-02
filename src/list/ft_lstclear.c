#include "minirt.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list	*lst;
	t_list	*tmp;

	if (!head)
		handle_error(ERR_LIST);
	lst = *head;
	while (lst)
	{
		tmp = lst;
		del(lst->data);
		lst = lst->next;
		free(tmp);
	}
	*head = NULL;
}
