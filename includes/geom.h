#ifndef GEOM_H
# define GEOM_H

typedef struct s_vec
{
	float x;
	float y;
	float z;
}				t_vec;


t_vec *v_new(float x, float y, float z);
t_vec *v_sub(t_vec *v1, t_vec *v2);
float v_len(t_vec *vec);
void v_norm(t_vec *v);
float v_dot_product(t_vec *v1, t_vec *v2);

#endif
