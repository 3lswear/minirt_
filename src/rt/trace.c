#include "minirt.h"

void trace(t_win *window, t_scene *scene)
{
	int mlx_x;
	int mlx_y;
	float x_ang;
	float y_ang;
	int color;
	t_vec *ray;
	t_view *viewport;

	float x_ray;
	float y_ray;
	
	mlx_y = 0;

	viewport = get_viewport(scene->width, scene->height, scene->cams->fov);
	y_ang = (scene->width / 2);
	while (y_ang >= (scene->height / 2) * -1)
	{
		y_ray = y_ang * viewport->y_pixel;
		x_ang = -(scene->width / 2);
		mlx_x = 0;
		while (x_ang <= scene->width / 2)
		{
			x_ray = x_ang * viewport->x_pixel;
			ray = new_vec(x_ray, y_ray, -1);
			v_norm(ray);
			if (inter_sphere(scene->cams, ray, scene->sphere))
				color = WHITE;
			else
				color = BLACK;
			/* pixel_put(window, mlx_x, mlx_y, color); */
			mlx_pixel_put(window->mlx, window->win, mlx_x, mlx_y, color);
			/* free(ray); */
			x_ang++;
			mlx_x++;
		}
		y_ang--;
		mlx_y++;
	}

}

t_view *get_viewport(float width, float height, float fov)
{
	t_view *viewport;
	float aspect_ratio;

	/* (void)width; */
	/* (void)height; */
	(void)fov;

	viewport = malloc(sizeof(t_view));
	if (!viewport)
		handle_error(-1);
	aspect_ratio = width / height;
	viewport->width = 1;
	viewport->height = viewport->width  / aspect_ratio;
	viewport->x_pixel = viewport->width / width;
	viewport->y_pixel = viewport->height / height;
	return (viewport);
}
