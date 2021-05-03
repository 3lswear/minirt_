#include "minirt.h"

void	print_progress(t_scene *scene, int y, t_win *win, char *string)
{
	int	index;

	index = (y / scene->height) * 100;
	string[index] = '#';
	mlx_string_put(win->mlx, win->win, (scene->width / 2) - 300,
		scene->height / 2, WHITE, string);
}

void	get_cam_basis(t_cam *cam)
{
	t_vec	*up;

	up = v_new(0, 1, 0);
	cam->rev_dir = v_mult(cam->dir, -1);
	v_norm_inplace(cam->rev_dir);
	cam->right = v_cross(up, cam->rev_dir);
	if (v_len(cam->right) == 0)
	{
		free(up);
		up = v_new(0, 0, -1);
		free(cam->right);
		cam->right = v_cross(up, cam->rev_dir);
	}
	print_vec(cam->right, "cam->right");
	v_norm_inplace(cam->right);
	cam->up = v_cross(cam->rev_dir, cam->right);
	print_vec(cam->up, "cam->up");
	v_norm_inplace(cam->up);
	free(up);
}

t_vec	*get_cam_ray(t_cam *cam, double x_ray, double y_ray)
{
	t_vec	*ray;
	t_vec	*result;

	ray = v_new(x_ray, y_ray, -1);
	v_norm_inplace(ray);
	result = v_new(
			((ray->x * cam->right->x) + (ray->y * cam->up->x)
				 + (ray->z * cam->rev_dir->x)),
			((ray->x * cam->right->y) + (ray->y * cam->up->y)
				 + (ray->z * cam->rev_dir->y)),
			((ray->x * cam->right->z) + (ray->y * cam->up->z)
				 + (ray->z * cam->rev_dir->z))
			);
	v_norm_inplace(result);
	free(ray);
	return (result);
}

void	trace(t_win *window, t_scene *scene, t_cam *cam, int save_bmp)
{
	t_view	*view;
	struct s_trace tr;
	char	string[101];

	ft_memset(string, '-', 100);
	string[100] = 0;
	view = get_viewport(scene->width, scene->height, cam->fov);
	tr.mlx_y = 0;
	get_cam_basis(cam);
	while (tr.mlx_y <= scene->height)
	{
		tr.ray_y = (-tr.mlx_y + scene->height / 2) * view->y_pixel;
		tr.mlx_x = 0;
		while (tr.mlx_x <= scene->width)
		{
			tr.ray_x = (tr.mlx_x - scene->width / 2) * view->x_pixel;
			cam->ray = get_cam_ray(cam, tr.ray_x, tr.ray_y);
			tr.color = inter_objects(cam, scene);
			if (tr.color.r * tr.color.g * tr.color.b < 0)
				tr.color = c_mul_scalar(scene->ambient, scene->amb_intensity);
			pixel_put(window, tr.mlx_x, tr.mlx_y, argb_color(tr.color));
			free(cam->ray);
			tr.mlx_x++;
		}
		if (!save_bmp)
			print_progress(scene, tr.mlx_y, window, string);
		tr.mlx_y++;
	}
	free(view);
}

t_view	*get_viewport(double width, double height, double fov)
{
	t_view	*viewport;
	double	aspect_ratio;

	viewport = malloc(sizeof(t_view));
	if (!viewport)
		handle_error(-1);
	aspect_ratio = width / height;
	viewport->width = 2 * tan((fov / 2) * (M_PI / 180));
	viewport->height = viewport->width / aspect_ratio;
	viewport->x_pixel = viewport->width / width;
	viewport->y_pixel = viewport->height / height;
	printf("viewport->x_pixel = %f\n", viewport->x_pixel);
	printf("viewport->y_pixel = %f\n", viewport->y_pixel);
	printf("viewport->height = %f\n", viewport->height);
	return (viewport);
}
