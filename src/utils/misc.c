#include "minirt.h"

void	print_vec(t_vec *vec, char *label)
{
	printf("%s => %lf %lf %lf\n", label, vec->x, vec->y, vec->z);
}

void	lst_print(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->data, 1);
		ft_putstr_fd(" -> ", 1);
		lst = lst->next;
	}
	ft_putendl_fd("", 1);
}

void	print_str_array(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		printf("[%s]\t", data[i]);
		i++;
	}
	printf("\n");
}

void	obj_lst_print(t_list *lst)
{
	printf("   ");
	while (lst)
	{
		print_str_array(lst->data);
		printf("-> ");
		lst = lst->next;
	}
	printf("NULL\n");
}
