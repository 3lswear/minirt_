/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:24:28 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/27 19:38:20 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H


#define R_MASK	0x00FF0000
#define G_MASK	0x0000FF00
#define B_MASK	0x000000FF

# define WHITE	0x00FFFFFF
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define BLACK	0x00000000

# define ERR_ALLOC	-1
# define ERR_LIST	-2
# define ERR_ARG	-3
# define ERR_SUBNORM -4
# define ERR_NEG -5

# define SHININESS	100

# define KEY_Q 113


#include "../mlx-linux/mlx.h"
#include "../ext/gnl/get_next_line.h"
#include "../ext/libft/libft.h"
     #include <stdio.h>
#include "float.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef int t_color;

/* typedef struct	s_color */
/* { */
/* 	float r; */
/* 	float g; */
/* 	float b; */
/* } 				t_color; */

typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_win;
 
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

#include "geom.h"
#include "camera.h"
#include "scene.h"
#include "utils.h"
#include "objects.h"
#include "rt.h"
#include "inter.h"

#define RAD (M_PI / 180)

#define T_SPHERE 1
#define T_PLANE 2
#define T_SQUARE 3

/* typedef enum e_type {sphere, plane} t_type; */

typedef union u_object
{
	t_sphere sphere;
	t_plane plane;
	t_square square;
} t_object;

typedef struct s_obj
{
	int type;
	t_object obj;

}	t_obj;


void	pixel_put(t_win *window, int x, int y, int color);
void	trace(t_win *window, t_scene *scene);

#endif
