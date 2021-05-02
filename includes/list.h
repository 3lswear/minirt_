#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}			t_list;

t_list	*ft_lstnew(void *data);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **head, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **head, t_list *new);
void	ft_lstadd_front(t_list **head, t_list *new);
size_t	ft_lstsize(t_list *list);

#endif
