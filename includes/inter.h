#ifndef INTER_H
# define INTER_H

typedef struct s_candidate
{
	t_color	color;
	double	dist;
}	t_candidate;

typedef struct s_hit
{
	double a;
	double b;
}				t_hit;


double get_positive(t_hit hit);
double just_get(t_hit hit);

t_color	inter_objects(t_cam *cam, t_scene *scene);
t_hit	inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere);
double	inter_plane(t_vec *origin, t_vec *ray, t_plane *plane);
double	inter_triang(t_vec *origin, t_vec *ray, t_triang *tri);
double inter_square(t_point *origin, t_vec *ray, t_square *square);

/* t_candidate	*cand_new(t_color color, double dist); */
t_color	choose_candidate(t_list **list);

t_color	calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, double ray_min);
t_color	calc_lights_2s(t_vec *norm, t_scene *scene, t_vec *ray, double ray_min, t_cam *cam);

t_color	calc_light_matte(t_vec *n, t_light *light, t_vec *ray, double ray_len, t_cam *cam);
t_color	calc_light_shiny(t_sphere *sphere, t_light *light,
			t_vec *ray, double ray_len);

typedef struct s_moller
{
	double	determ;
	double	u;
	double	v;
	double	t;
	t_vec	*pvec;
	t_vec	*tvec;
	t_vec	*qvec;

}	t_moller;

#endif
