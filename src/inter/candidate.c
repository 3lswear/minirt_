#include "minirt.h"

t_candidate *cand_new(t_color color, double dist)
{
	t_candidate *result;

	result = malloc(sizeof(t_candidate));
	if (!result)
		handle_error(ERR_ALLOC);
	result->color = color;
	result->dist = dist;
	return (result);
}

t_color choose_candidate(t_list **list)
{
	t_list *current;
	double dist_min;
	t_candidate *cand;
	t_candidate *winner;

	dist_min = INFINITY;
	winner = NULL;

	current = *list;
	while (current)
	{
		cand = current->data;
		if (cand->dist < dist_min)
			winner = cand;

		current = current->next;
	}

	if (winner)
		return (winner->color);
	else
		return (-1);
}
