#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_cam
{
	t_vec		*origin;
	t_vec		*dir;
	double		fov;
	t_vec		*ray;
	t_vec		*up;
	t_vec		*right;
	t_vec		*rev_dir;

}				t_cam;

t_cam	*new_cam(t_vec *origin, t_vec *dir, double fov);
void	get_cam_basis(t_cam *cam);

/* t_color argb_color(int r, int g, int b); */
int		argb_color(t_color color);
t_color	c_add(t_color color1, t_color color2);
t_color	c_mul_scalar(t_color color, double mul);
t_color	c_mul(t_color color1, t_color color2);
t_color	new_color(int r, int g, int b);

#endif
