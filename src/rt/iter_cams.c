#include "minirt.h"

void	free_cam_basis(t_cam *cam)
{
	free4(cam->rev_dir, cam->right, cam->up, NULL);
}

void	next_cam(t_scene *scene, t_win *window, t_cam *cam, int save_bmp)
{
	window->img = mlx_new_image(window->mlx, scene->width, scene->height);
	window->addr = mlx_get_data_addr(window->img, &window->bpp, &window->line_l,
			&window->en);
	trace(window, scene, cam, save_bmp);
	free_cam_basis(cam);
	if (save_bmp)
		save_screen(window, scene);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

int	close_button(int keycode, void *scene)
{
	(void)keycode;
	exit_by_close(NULL, scene);
	return (0);
}

int	key_press_hook(int keycode, struct s_data *data)
{
	if (keycode == KEY_Q || keycode == KEY_ESC)
	{
		graceful_exit(data->win, data->scene, 0);
		return (1337);
	}
	else if (keycode == KEY_SPC)
	{
		if (data->current->next)
		{
			data->current = data->current->next;
			data->cam = data->current->data;
			mlx_destroy_image(data->win->mlx, data->win->img);
			free(data->cam->ray);
			next_cam(data->scene, data->win, data->cam, 0);
		}
		else
			printf("No more cameras!\n");
		return (2);
	}
	else
	{
		return (0);
	}
}

void	iter_cams(t_scene *scene, t_win *window, int save_bmp)
{
	t_cam			*cam;
	struct s_data	data;

	cam = scene->cams->data;
	data.win = window;
	data.scene = scene;
	data.current = scene->cams;
	data.cam = cam;
	if (!save_bmp)
		window->win = mlx_new_window(window->mlx, scene->width,
				scene->height, "miniRT");
	next_cam(scene, window, cam, save_bmp);
	mlx_hook(window->win, 33, 3, close_button, (void *) scene);
	mlx_hook(window->win, 2, 1L << 0, (void *) key_press_hook, (void *) &data);
	mlx_loop(window->mlx);
	exit(0);
}
