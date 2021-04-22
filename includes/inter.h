#ifndef INTER_H
# define INTER_H


int inter_objects(t_cam *cam, t_vec *ray, t_scene *scene);
int inter_sphere(t_cam *cam, t_vec *ray, t_sphere *sphere);
#endif
