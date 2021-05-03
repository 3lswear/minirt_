#include "minirt.h"

t_color	calc_light_matte(t_vec *n, t_light *light, double ray_len, t_cam *cam)
{
	t_point	*surface_point;
	t_vec	*l;
	double	strength;

	surface_point = v_mult(cam->ray, ray_len);
	v_add_inplace(surface_point, cam->origin);
	l = v_sub(light->coords, surface_point);
	v_norm_inplace(n);
	strength = v_dot_product(n, l) / (v_len(l) * v_len(n));
	free(surface_point);
	if (v_dot_product(n, l) > 0)
	{
		free(l);
		return (c_mul_scalar(light->color, (light->brightess * strength)));
	}
	else
	{
		free(l);
		return (new_color(0, 0, 0));
	}
}
