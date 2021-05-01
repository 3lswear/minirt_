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

t_vec *get_cam_ray(t_cam *cam, double x_ray, double y_ray)
{
	t_vec *ray;
	double z;
	t_vec *actual_dir;
	t_vec *up;
	t_vec *cam_right;
	t_vec *cam_up;

	/* t_vec *lookat; */
	t_vec *result;

	z = -1;
	ray = v_new(x_ray, y_ray, z);
	/* ray = v_new(x_ray - cam->origin->x, y_ray - cam->origin->y, z - cam->origin->z); */
	v_norm_inplace(ray);


	actual_dir = v_mult(cam->dir, -1);
	/* actual_dir = v_sub(cam->origin, cam->dir); */
	/* actual_dir = v_add(cam->origin, cam->dir); */
	/* v_mult_inplace(actual_dir, -1); */
	/* actual_dir = v_new(cam->dir->x, cam->dir->y, -cam->dir->z); */
	/* actual_dir = v_add(actual_dir, cam->origin); */
	v_norm_inplace(actual_dir);
	/* print_vec(actual_dir, "actual_dir"); */

	up = v_new(0, 1, 0);
	cam_right = v_cross(up, actual_dir);
	/* print_vec(cam_right, "cam_right "); */
	v_norm_inplace(cam_right);
	cam_up = v_cross(actual_dir, cam_right);
	/* print_vec(cam_up, "cam_up "); */
	v_norm_inplace(cam_up);

	/* ray = v_sub(ray, cam->origin); */
	/* result = v_new( */
	/* 		((ray->x * cam_right->x) + (ray->y * cam_right->y) + (ray->z * cam_right->z)), */
	/* 		((ray->x * cam_up->x) + (ray->y * cam_up->y) + (ray->z * cam_up->z)), */
	/* 		((ray->x * actual_dir->x) + (ray->y * actual_dir->y) + (ray->z * actual_dir->z)) */
	/* 		); */
	/* v_sub_inplace(ray, cam->origin); */

	result = v_new(
			((ray->x * cam_right->x) + (ray->y * cam_up->x) + (ray->z * actual_dir->x)),
			((ray->x * cam_right->y) + (ray->y * cam_up->y) + (ray->z * actual_dir->y)),
			((ray->x * cam_right->z) + (ray->y * cam_up->z) + (ray->z * actual_dir->z))
			);


	/* result->z += 0.7; */
	v_norm_inplace(result);
	/* print_vec(result, "transormed vec\n\n\n"); */

	free(actual_dir);

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
