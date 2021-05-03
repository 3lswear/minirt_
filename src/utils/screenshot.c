#include "minirt.h"

static void	int_to_bytes(int len, unsigned char *bytes)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		bytes[i] = len % 0x100;
		len /= 0x100;
		i++;
	}
}

static void	write_header(t_win *win, t_scene *scene, int fd)
{
	unsigned char	bytes[4];
	int				len;
	int				x;
	int				y;

	x = scene->width;
	y = scene->height;
	len = y * win->line_l + x * (win->bpp / 8);
	write(fd, "BM", 2);
	int_to_bytes(len + 54, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\66\0\0\0\50\0\0\0", 12);
	int_to_bytes(x, bytes);
	write(fd, bytes, 4);
	int_to_bytes(y, bytes);
	write(fd, bytes, 4);
	write(fd, "\1\0\40\0\0\0\0\0", 8);
	int_to_bytes(0, bytes);
	write(fd, bytes, 4);
	int_to_bytes(x, bytes);
	write(fd, bytes, 4);
	int_to_bytes(y, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
}

void	write_file(t_win *win, t_scene *scene, int fd)
{
	int	i;
	int	x;

	write_header(win, scene, fd);
	i = scene->height - 1;
	x = scene->width;
	while (i >= 0)
	{
		write(fd, win->addr + i * win->line_l, x * (win->bpp / 8));
		i--;
	}
	close(fd);
}

void	save_screen(t_win *win, t_scene *scene)
{
	int	fd;

	fd = open("out.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (!fd)
		handle_error(ERR_FILE);
	write_file(win, scene, fd);
	printf("File save successful!\n");
	graceful_exit(win, scene, 1);
	exit(0);
}
