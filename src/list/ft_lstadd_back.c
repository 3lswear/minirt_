#include "minirt.h"

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list *last;

	if (!new || !head)
		handle_error(ERR_LIST);
	if (!(*head))
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		last = ft_lstlast(*head);
		last->next = new;
	}
}
