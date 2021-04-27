#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_sphere
{
	t_point	*center;
	float 		diam;
	int 		color;
} 				t_sphere;

t_sphere new_sphere(t_vec *center, float diam);

typedef struct s_plane
{
	t_point *pos;
	t_vec *norm;
	t_color color;
}				t_plane;

t_plane new_plane(t_point *pos, t_vec *norm);

typedef struct s_square
{
	t_point *pos;
	t_vec *norm;
	float	side;
	t_color color;
} t_square;

t_square new_square(t_point *pos, t_vec *norm, float side, t_color color);

#endif
