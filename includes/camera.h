#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_cam
{
	t_vec 		*origin;
	t_vec		*dir;
	float		fov;

}				t_cam;

t_cam *new_cam(t_vec *origin, t_vec *dir, float fov);
t_color argb_color(int r, int g, int b);
/* int argb_color(t_color color); */
t_color c_add(t_color color1, t_color color2);
t_color c_mul_scalar(t_color color, float mul);
t_color c_mul(t_color color1, t_color color2);

#endif
