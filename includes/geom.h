#ifndef GEOM_H
# define GEOM_H

typedef struct s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

typedef t_vec t_point;


t_vec *v_new(float x, float y, float z);
t_vec *v_sub(t_vec *v1, t_vec *v2);
float v_len(t_vec *vec);
void v_norm(t_vec *v);
float v_dot_product(t_vec *v1, t_vec *v2);
t_vec *v_mult(t_vec *vec, float mult);
int v_equal(t_vec *v1, t_vec *v2);

typedef struct	s_light
{
	t_vec	*coords;
	float	brightess;
	int		color;
} 				t_light;

t_light *l_new(t_vec *coords, float brightess, int color);

#endif
