#ifndef GEOM_H
# define GEOM_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef t_vec	t_point;

t_vec	*v_new(double x, double y, double z);
t_vec	v_new_s(double x, double y, double z);
t_vec	*v_sub(t_vec *v1, t_vec *v2);
double	v_len(t_vec *vec);
double	v_dot_product(t_vec *v1, t_vec *v2);
t_vec	*v_mult(t_vec *vec, double mult);
int		v_equal(t_vec *v1, t_vec *v2);
t_vec	*v_cross(t_vec *a, t_vec *b);
t_vec	*v_add(t_vec *a, t_vec *b);
t_vec	*v_norm(t_vec *vec);

void	v_norm_inplace(t_vec *v);
void	v_sub_inplace(t_vec *a, t_vec *b);
void	v_add_inplace(t_vec *a, t_vec *b);
void	v_mult_inplace(t_vec *vec, double mult);

typedef struct s_light
{
	t_vec		*coords;
	double		brightess;
	t_color		color;
}				t_light;

t_light	*l_new(t_vec *coords, double brightess, t_color color);

#endif
