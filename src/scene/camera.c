#include "minirt.h"

t_cam	*new_cam(t_vec *origin, t_vec *dir, double fov)
{
	t_cam	*result;

	result = malloc(sizeof(t_cam));
	if (!result)
		handle_error(-1, -1);
	result->origin = origin;
	result->dir = dir;
	result->fov = fov;
	return (result);
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
	v_norm_inplace(cam->right);
	cam->up = v_cross(cam->rev_dir, cam->right);
	v_norm_inplace(cam->up);
	free(up);
}
