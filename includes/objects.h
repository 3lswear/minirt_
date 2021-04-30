#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_sphere
{
	t_point	*center;
	double 		diam;
	int 		color;
} 				t_sphere;

t_sphere new_sphere(t_vec *center, double diam);

typedef struct s_plane
{
	t_point *pos;
	t_vec *norm;
	t_color color;
}				t_plane;

t_plane new_plane(t_point *pos, t_vec *norm, t_color color);

typedef struct s_square
{
	t_point *pos;
	t_vec *norm;
	double	side;
	t_color color;
} t_square;

t_square new_square(t_point *pos, t_vec *norm, double side, t_color color);

typedef struct s_triang
{
	t_point *a;
	t_point *b;
	t_point *c;
	t_color color;
	t_vec *norm;
} t_triang;

t_triang new_triang(t_point *a, t_point *b, t_point *c, t_color color);
t_vec *triang_get_norm(t_triang *tri);

#endif
