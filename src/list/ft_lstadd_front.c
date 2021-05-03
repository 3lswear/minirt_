#include "minirt.h"

void	ft_lstadd_front(t_list **head, t_list *new)
{
	if (!new || !head || !(*head))
		handle_error(ERR_LIST, -1);
	new->next = *head;
	*head = new;
}
