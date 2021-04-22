#ifndef INTER_H
# define INTER_H


int inter_objects(t_cam *cam, t_vec *ray, t_scene *scene);
float inter_sphere(t_vec *origin, t_vec *ray, t_sphere *sphere);
#endif
