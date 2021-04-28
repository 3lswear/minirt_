#ifndef INTER_H
# define INTER_H


typedef struct s_candidate
{
	t_color color;
	float dist;
}	t_candidate;

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene);
float inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere);
float inter_plane(t_vec *origin, t_vec *ray, t_plane *plane);
float	inter_triang(t_vec *origin, t_vec *ray, t_triang *tri);

t_candidate *cand_new(t_color color, float dist);
t_color choose_candidate(t_list **list);

t_color calc_lights(t_vec *norm, t_scene *scene, t_vec *ray, float ray_min);
t_color calc_lights_2s(t_vec *norm, t_scene *scene, t_vec *ray, float ray_min);

t_color calc_light_matte(t_vec *n, t_light *light, t_vec *ray, float ray_len);
t_color calc_light_shiny(t_sphere *sphere, t_light *light, t_vec *ray, float ray_len);

#endif
