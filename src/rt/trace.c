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

	

	viewport = get_viewport(scene->width, scene->height, scene->cams->fov);
	printf("scene->height / 2 * -1 = %f\n", -(scene->height / 2));
	y_ang = (scene->height / 2);
	mlx_y = 0;
	while (y_ang >= -(scene->height / 2))
	{
		y_ray = y_ang * viewport->y_pixel;
		x_ang = -(scene->width / 2);
		mlx_x = 0;
		while (x_ang <= scene->width / 2)
		{
			x_ray = x_ang * viewport->x_pixel;
			ray = v_new(x_ray, y_ray, -1);
			v_norm(ray);
			color = inter_objects(scene->cams, ray, scene->objs);
			if (color < 0)
				color = BLACK;
			pixel_put(window, mlx_x, mlx_y, color);
			/* printf("x, y\t\t=>%10d\t%10d\n", mlx_x, mlx_y); */
			/* printf("x_ang, y_ang\t=> %10f\t%10f\n", x_ang, y_ang); */
			/* mlx_pixel_put(window->mlx, window->win, mlx_x, mlx_y, color); */
			free(ray);
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

	viewport = malloc(sizeof(t_view));
	if (!viewport)
		handle_error(-1);
	aspect_ratio = width / height;
	viewport->width = 2 * tan((fov / 2) * RAD);
	viewport->height = viewport->width  / aspect_ratio;
	viewport->x_pixel = viewport->width / width;
	viewport->y_pixel = viewport->height / height;
	printf("viewport->x_pixel = %f\n", viewport->x_pixel);
	printf("viewport->y_pixel = %f\n", viewport->y_pixel);
	printf("viewport->height = %f\n", viewport->height);
	return (viewport);
}
