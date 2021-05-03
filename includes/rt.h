#ifndef RT_H
# define RT_H

typedef struct s_viewport
{
	double	width;
	double	height;
	double	x_pixel;
	double	y_pixel;
}	t_view;

struct s_data
{
	t_win	*win;
	t_scene	*scene;
	t_list	*current;
	t_cam	*cam;
};

t_view	*get_viewport(double width, double height, double fov);
void	trace(t_win *window, t_scene *scene, t_cam *cam, int save_bmp);
void	iter_cams(t_scene *scene, t_win *window, int save_bmp);

#endif
