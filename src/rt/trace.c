#include "minirt.h"

void print_progress(t_scene *scene, int x, int y, t_win *window, char *string)
{
	int index;
	/* if ((x * y) % 10) */
	/* 	return; */
	/* printf("\rprogress is %.1f%%", floor(((x * y) / (scene->height * scene->width)) * 100)); */
	(void)x;
	/* (void)string; */
	/* (void)scene; */
	/* (void)index; */
	index = (y / scene->height) * 100;
	/* printf("%d\n", index); */
	string[index] = '#';
	mlx_string_put(window->mlx, window->win, (scene->width / 2) - 300, scene->height / 2, WHITE, string);
	/* mlx_string_put(window->mlx, window->win, x, y, WHITE, "#######"); */
}

void	get_cam_basis(t_cam *cam)
{
	t_vec *up;

	up = v_new(0, 1, 0);
	cam->rev_dir = v_mult(cam->dir, -1);
	v_norm_inplace(cam->rev_dir);

	cam->right = v_cross(up, cam->rev_dir);
	if (v_len(cam->right) == 0)
	{
		printf("jopa\n");
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

t_vec *get_cam_ray(t_cam *cam, double x_ray, double y_ray)
{
	t_vec *ray;
	t_vec *result;

	ray = v_new(x_ray, y_ray, -1);
	v_norm_inplace(ray);
	result = v_new(
			((ray->x * cam->right->x) + (ray->y * cam->up->x) + (ray->z * cam->rev_dir->x)),
			((ray->x * cam->right->y) + (ray->y * cam->up->y) + (ray->z * cam->rev_dir->y)),
			((ray->x * cam->right->z) + (ray->y * cam->up->z) + (ray->z * cam->rev_dir->z))
			);
	v_norm_inplace(result);
	free(ray);
	return (result);
}

void trace(t_win *window, t_scene *scene, t_cam *cam)
{
	int mlx_x;
	int mlx_y;
	double x_ang;
	double y_ang;
	int color;
	/* t_vec *ray; */
	t_view *viewport;

	double x_ray;
	double y_ray;

	char string[101];

	ft_memset(string, '-', 100);
	string[100] = 0;
	viewport = get_viewport(scene->width, scene->height, cam->fov);
	printf("scene->height / 2 * -1 = %f\n", -(scene->height / 2));
	y_ang = (scene->height / 2);
	mlx_y = 0;
	/* printf("ambient: %X\n", scene->ambient); */
	/* printf("sphere: %X\n", ((t_sphere *)(scene->spheres->data))->color); */
	/* printf("combined: %X\n", c_add(((t_sphere *)(scene->spheres->data))->color, scene->ambient)); */
	get_cam_basis(cam);
	while (y_ang >= -(scene->height / 2))
	{
		y_ray = y_ang * viewport->y_pixel;
		x_ang = -(scene->width / 2);
		mlx_x = 0;
		while (x_ang <= scene->width / 2)
		{
			x_ray = x_ang * viewport->x_pixel;
			cam->ray = get_cam_ray(cam, x_ray, y_ray);
			/* cam->ray = v_new(x_ray, y_ray, -1); */
			color = inter_objects(cam, scene);
			if (color < 0)
				color = c_mul_scalar(scene->ambient, scene->amb_intensity);
			/* pixel_put(window, mlx_x, mlx_y, argb_color(color)); */
			pixel_put(window, mlx_x, mlx_y, color);
			/* printf("x, y\t\t=>%10d\t%10d\n", mlx_x, mlx_y); */
			/* printf("x_ang, y_ang\t=> %10f\t%10f\n", x_ang, y_ang); */
			/* mlx_pixel_put(window->mlx, window->win, mlx_x, mlx_y, color); */
			free(cam->ray);
			x_ang++;
			mlx_x++;
		}
		print_progress(scene, mlx_x, mlx_y, window, string);
		y_ang--;
		mlx_y++;
	}
	free(viewport);
	printf("\n");
}

t_view *get_viewport(double width, double height, double fov)
{
	t_view *viewport;
	double aspect_ratio;

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
