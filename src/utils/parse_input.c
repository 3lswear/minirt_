#include "minirt.h"

void ft_putstr(void *str)
{
	ft_putstr_fd((char *)str, 1);
}

void lst_print(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->data, 1);
		ft_putstr_fd(" -> ", 1);
		lst = lst->next;
	}
	ft_putendl_fd("", 1);

}

void parse_input(char *file, t_scene *scene)
{
	int fd;
	char *line;
	int ret;
	char **data;
	fd = open(file, O_RDONLY);
	(void)scene;

	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("line from gnl => %s\n", line);
		data = split_ws(line);
		int splt_i = 0;
		while (data[splt_i])
		{
			printf("[%s]\n", data[splt_i]);
			splt_i++;
		}

		free(line);
	}
	if (!ret)
		free(line);


	printf("testing lists!!!!!\n");

	/* t_list *pog =  ft_lstnew("pogchamp"); */
	/* t_list *pepega =  ft_lstnew("pepega"); */
	/* t_list *lul =  ft_lstnew("lul"); */
	/* ft_lstadd_back(&pog, pepega); */
	/* ft_lstadd_back(&pog, lul); */

	/* lst_print(pog); */
	/* handle_error(ERR_ALLOC); */

	
	/* printf("gnl returned -> [%d]\n", ret); */

	close(fd);
}
