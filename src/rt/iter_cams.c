#include "minirt.h"

void	free_cam_basis(t_cam *cam)
{
	free4(cam->rev_dir, cam->right, cam->up, NULL);
}

static void	dec_hex_endian(int len, unsigned char *size)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		size[i] = len % 256;
		len /= 256;
	}
}

static void	write_header(t_win *win, t_scene *scene, int fd)
{
	unsigned char	bytes[4];
	int				len;
	int x;
	int y;

	x = scene->width;
	y = scene->height;
	len = y * win->line_l + x * (win->bpp / 8);
	write(fd, "BM", 2);
	dec_hex_endian(len + 54, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\66\0\0\0\50\0\0\0", 12);
	dec_hex_endian(x, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(y, bytes);
	write(fd, bytes, 4);
	write(fd, "\1\0\40\0\0\0\0\0", 8);
	dec_hex_endian(0, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(x, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(y, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
}

void write_file(t_win *win, t_scene *scene, int fd)
{
	int i;
	int x;

	write_header(win, scene, fd);
	i = scene->height;
	x = scene->width;
	/* printf("i %d\n", i); */
	/* printf("x %d\n", x); */
	while (--i >= 0)
	{
	printf("i %d\n", i);
		write(fd, win->addr + i * win->line_l, x * (win->bpp / 8));

	}
	close(fd);


}

void save_screen(t_win *win, t_scene *scene)
{
	int fd;

	fd = open("out.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (!fd)
		handle_error(ERR_FILE);
	write_file(win, scene, fd);
	printf("File save successful!\n");
	/* graceful_exit(win, scene); */
	exit(0);
}

void	next_cam(t_scene *scene, t_win *window, t_cam *cam, int save_bmp)
{
	window->img = mlx_new_image(window->mlx, scene->width, scene->height);
	window->addr = mlx_get_data_addr(window->img, &window->bpp, &window->line_l, 
			&window->en);
	trace(window, scene, cam, save_bmp);
	free_cam_basis(cam);
	/* free(cam->ray); */
	/* loop and hook to switch to the next one */
	if (save_bmp)
		save_screen(window, scene);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

int		close_button(int keycode, void *scene)
{
	(void)keycode;
	exit_by_close(NULL, scene);

	return (0);
}

int		key_press_hook(int keycode, struct s_data *data)
{
	if (keycode == KEY_Q || keycode == KEY_ESC)
	{
		graceful_exit(data->win, data->scene);
		return (1337);
	}
	else if (keycode == KEY_SPC)
	{
		/* printf("space pressed\n"); */
		if (data->current->next)
		{
			data->current = data->current->next;
			data->cam = data->current->data;
			mlx_destroy_image(data->win->mlx, data->win->img);
			free(data->cam->ray);
			next_cam(data->scene, data->win, data->cam, 0);
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

void	iter_cams(t_scene *scene, t_win *window, int save_bmp)
{
	t_cam			*cam;
	struct s_data	*data;

	data = malloc(sizeof(struct s_data));
	cam = scene->cams->data;
	data->win = window;
	data->scene = scene;
	data->current = scene->cams;
	data->cam = cam;
	if (!save_bmp)
		window->win = mlx_new_window(window->mlx, scene->width, scene->height, "🤠🤠🤠");
	next_cam(scene, window, cam, save_bmp);
	mlx_hook(window->win, 33, 3, close_button, (void *)scene);
	mlx_hook(window->win, 2, 1L<<0, (void *)key_press_hook , (void *)data);
	mlx_loop(window->mlx);
	exit(0);
}
