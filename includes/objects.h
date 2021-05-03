#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_sphere
{
	t_point	*center;
	double	diam;
	t_color	color;
}	t_sphere;

t_sphere	new_sphere(t_vec *center, double diam);

typedef struct s_plane
{
	t_point	*pos;
	t_vec	*norm;
	t_color	color;
}				t_plane;

t_plane		new_plane(t_point *pos, t_vec *norm, t_color color);

typedef struct s_square
{
	t_point	*pos;
	t_vec	*norm;
	double	side;
	double	hside;
	t_color	color;
	t_point	*a;
	t_point	*b;
	t_point	*c;
	t_point	*d;
}	t_square;

t_square	new_square(t_point *pos, t_vec *norm, double side, t_color color);
void		sq_get_vertices(t_square *square);

typedef struct s_triang
{
	t_point	*a;
	t_point	*b;
	t_point	*c;
	t_color	color;
	t_vec	*norm;
	t_vec	*edge1;
	t_vec	*edge2;
}	t_triang;

t_triang	new_triang(t_point *a, t_point *b, t_point *c, t_color color);
t_vec		*triang_get_norm(t_triang *tri);

typedef struct s_cylind
{
	t_point	*pos;
	t_vec	*norm;
	double	diam;
	double	rad;
	double	height;
	t_color	color;
	t_vec	*cur_norm;

}	t_cylind;

typedef union u_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_square	square;
	t_triang	triang;
	t_cylind	cylind;
}	t_object;

typedef struct s_obj
{
	int			type;
	t_color		color;
	t_object	obj;

}	t_obj;

t_cylind	new_cylind(t_point *pos, t_vec *norm, double diam, double height);
t_obj	*new_object(int type, t_object *object);

#endif
