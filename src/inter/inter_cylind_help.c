#include "minirt.h"

double	inter_disk(t_point *origin, t_vec *ray, t_plane *plane, double rad)
{
	double	plane_hit;
	t_point	*surface_point;
	t_vec	*v;
	double	d2;

	plane_hit = inter_plane(origin, ray, plane);
	if (plane_hit > 0)
	{
		surface_point = v_mult(ray, plane_hit);
		v_add_inplace(surface_point, origin);
		v = v_sub(surface_point, plane->pos);
		d2 = v_dot_product(v, v);
		free(surface_point);
		free(v);
		if (sqrt(d2) <= rad)
			return (plane_hit);
	}
	return (-1);
}

void	set_tube_norm(t_point *surface_point, t_cylind *cy,
		t_point *cap_pos, double m)
{
	t_point	*center;
	t_vec	*norm_x_m;

	norm_x_m = v_mult(cy->norm, m);
	center = v_add(cap_pos, norm_x_m);
	cy->cur_norm = v_sub(surface_point, center);
	v_norm_inplace(cy->cur_norm);
	free(norm_x_m);
	free(surface_point);
	free(center);
}

t_point	*get_surface(t_point *origin, t_vec *ray, double len)
{
	t_point	*surface_point;

	surface_point = v_mult(ray, len);
	v_add_inplace(surface_point, origin);
	return (surface_point);
}

t_hit	solve_quad(t_vec *ray, t_cylind *cy, t_vec *cam2cent)
{
	t_quad	quad;

	quad.a = v_dot_product(ray, ray) - pow(v_dot_product(ray, cy->norm), 2);
	quad.b = v_dot_product(ray, cam2cent) - v_dot_product(ray, cy->norm)
		* v_dot_product(cam2cent, cy->norm);
	quad.c = v_dot_product(cam2cent, cam2cent)
		- pow(v_dot_product(cam2cent, cy->norm), 2) - pow(cy->rad, 2);
	quad.b = quad.b * 2.0;
	quad.discr = (quad.b * quad.b) - (4 * quad.a * quad.c);
	if (quad.discr < 0)
		return (h_new(0, 0));
	return (h_new(
			(-quad.b - sqrt(quad.discr)) / (2 * quad.a),
			(-quad.b + sqrt(quad.discr)) / (2 * quad.a)
		));
}

double	calc_m(t_cylind *cy, t_hit tube_hits, t_vec *cam2cent, t_vec *ray)
{
	double	m1;
	t_vec	*tmp;

	tmp = v_mult(cy->norm, get_positive(tube_hits));
	m1 = v_dot_product(ray, tmp) + v_dot_product(cam2cent, cy->norm);
	free(tmp);
	return (m1);
}
