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

// t_color calc_light_shiny(t_sphere *sphere,
// t_light *light, t_vec *ray, double ray_len) {
// 	t_point *surface_point;
// 	t_vec *n;
// 	t_vec *l;
// 	t_vec *r;
// 	t_vec *v;
// 	double strength;

// 	surface_point = v_mult(ray, ray_len);
// 	v = v_mult(surface_point, -1);
// 	l = v_sub(light->coords, surface_point);
// 	n = v_sub(surface_point, sphere->center);
// 	v_norm_inplace(n);
// 	r = v_sub(v_mult(n, 2 * v_dot_product(n, l)), l);
// 	/* strength = v_dot_product(n, l) / (v_len(l) * v_len(n)); */
// 	strength = pow(v_dot_product(r, v) / (v_len(r) * v_len(v)), SHININESS);
// 	if (v_dot_product(r, v) > 0)
// 	{
// 		printf("strength => %f\n", strength);
// 		printf("bri * stre => %f\n", light->brightess * strength);
// 		return(c_mul_scalar(light->color, (light->brightess * strength)));
// 	}
// 	else
// 		return (new_color(0, 0, 0));
// }
