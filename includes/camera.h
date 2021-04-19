#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_cam
{
	t_vec 		*origin;
	t_vec		*dir;
	float		fov;

}				t_cam;

t_cam *new_cam(t_vec *origin, t_vec *dir, float fov);

#endif