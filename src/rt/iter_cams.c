#include "minirt.h"

void	free_cam_basis(t_cam *cam)
{
	free4(cam->rev_dir, cam->right, cam->up, NULL);
}

int idk_hook(int keycode, struct s_data *data)
{
	graceful_exit(data->win, data->scene);
	printf("keycode => %d\n", keycode);
	return (1337);
}

void next_cam(t_scene *scene, t_win *window, t_cam *cam)
{
	window->img = mlx_new_image(window->mlx, scene->width, scene->height);
	window->addr = mlx_get_data_addr(window->img, &window->bpp, &window->line_l, 
			&window->en);
	trace(window, scene, cam);
	free_cam_basis(cam);
	/* free(cam->ray); */
	/* loop and hook to switch to the next one */
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

int key_press_hook(int keycode, struct s_data *data)
{
	if (keycode == KEY_Q || keycode == KEY_ESC)
	{
		graceful_exit(data->win, data->scene);
		return (1337);
	}
	else if (keycode == KEY_SPC)
	{
		printf("space pressed\n");
		if (data->current->next)
		{
			data->current = data->current->next;
			data->cam = data->current->data;
			mlx_destroy_image(data->win->mlx, data->win->img);
			free(data->cam->ray);
			next_cam(data->scene, data->win, data->cam);
		}
		else
			printf("no more cams\n");
		return (2);
	}
	else
	{
		printf("keycode is 0x%X\n", keycode);
		return (0);
	}
}

void iter_cams(t_scene *scene, t_win *window)
{
	/* t_list *current; */
	t_cam *cam;
	struct s_data data;

	/* current = scene->cams; */
	cam = scene->cams->data;
	/* transform scene maybe */
	data.win = window;
	data.scene = scene;
	data.current = scene->cams;
	data.cam = cam;
	next_cam(scene, window, cam);
	/* mlx_hook(window->win, 17, 1L<<24, idk_hook , window); */
	/* mlx_loop_hook(window->mlx, key_press_hook, &data); */
	mlx_hook(window->win, 2, 1L<<0, (void *)key_press_hook , &data);
	mlx_hook(window->win, 33, 256, (void *)idk_hook, &data);
	mlx_loop(window->mlx);
	exit(0);
	/* current = current->next; */
}
