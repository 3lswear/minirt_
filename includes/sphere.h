#ifndef SPHERE_H
# define SPHERE_H

typedef struct	s_sphere
{
	t_vec	*center;
	float 		radius;
	int 		color;
} 				t_sphere;

t_sphere *new_sphere(t_vec *center, float radius);

#endif
