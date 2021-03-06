#ifndef INTER_H
# define INTER_H

typedef struct s_candidate
{
	t_color	color;
	double	dist;
}	t_candidate;

typedef struct s_hit
{
	double	a;
	double	b;
}				t_hit;

double	get_positive(t_hit hit);
double	just_get(t_hit hit);
t_hit	h_new(double a, double b);

t_color	inter_objects(t_cam *cam, t_scene *scene);

t_hit	inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere);
double	inter_plane(t_vec *origin, t_vec *ray, t_plane *plane);
double	inter_triang(t_vec *origin, t_vec *ray, t_triang *tri);
double	inter_square(t_point *origin, t_vec *ray, t_square *square);
t_hit	inter_cylind(t_point *origin, t_vec *ray, t_cylind *cy, int set_normal);

/* t_candidate	*cand_new(t_color color, double dist); */
t_color	choose_candidate(t_list **list);

t_color	calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, double ray_min);
t_color	calc_lights_2s(t_vec *norm, t_scene *scene, double ray_min, t_cam *cam);

t_color	calc_light_matte(t_vec *n, t_light *light, double ray_len, t_cam *cam);
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

typedef struct s_quad
{
	double	discr;
	double	a;
	double	b;
	double	c;
	t_hit	result;
}	t_quad;

typedef struct s_ic
{
	t_hit	tube_hits;
	t_hit	cap_hits;
	t_hit	result;
	double	m1;
	t_plane	cap1;
	t_plane	cap2;
	t_vec	*cam2cent;
	t_point	*point1;
	t_point	*point2;

}	t_ic;

double	inter_disk(t_point *origin, t_vec *ray, t_plane *plane, double rad);
void	set_tube_norm(t_point *surface_point, t_cylind *cy,
			t_point *cap_pos, double m);
t_point	*get_surface(t_point *origin, t_vec *ray, double len);
t_hit	solve_quad(t_vec *ray, t_cylind *cy, t_vec *cam2cent);
double	calc_m(t_cylind *cy, t_hit tube_hits, t_vec *cam2cent, t_vec *ray);

#endif
