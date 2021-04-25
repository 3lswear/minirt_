#ifndef INTER_H
# define INTER_H


typedef struct s_candidate
{
	t_color color;
	float dist;
}	t_candidate;

t_candidate *cand_new(t_color color, float dist);
t_color choose_candidate(t_list **list);

t_color inter_objects(t_cam *cam, t_vec *ray, t_scene *scene);
float inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere);
float inter_plane(t_vec *origin, t_vec *ray, t_plane *plane);
#endif
