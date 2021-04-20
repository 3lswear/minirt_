#ifndef UTILS_H
# define UTILS_H

float idiv(int a, int b);
void handle_error(int value);
void parse_input(char *file, t_scene *scene, t_win *window);
void	parse_res(char **line, t_scene *scene);


typedef struct	s_list
{
	struct s_list	*next;
	void	*data;

}				t_list;

t_list	*ft_lstnew(void *data);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **head, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **head, t_list *new);
void	ft_lstadd_front(t_list **head, t_list *new);
size_t	ft_lstsize(t_list *list);


int	iswhitespace(const char *chr);
char	**split_ws(char const *s);
char	*strchr_ws(const char *s);

#endif
