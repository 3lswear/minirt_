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

static double calc_m(t_cylind *cy, t_hit tube_hits, t_vec *cam2cent, t_vec *ray)
{
	double	m1;
	t_vec	*tmp;

	tmp = v_mult(cy->norm, get_positive(tube_hits));
	m1 = v_dot_product(ray, tmp) + v_dot_product(cam2cent, cy->norm);
	free(tmp);
	return (m1);
}

static t_vec	*calc_cam2cent(t_point *origin, t_cylind *cy)
{
	t_vec	*cam2cent;
	t_vec	*norm_mult;
	t_vec	*center;

	norm_mult = v_mult(cy->norm, cy->height / 2);
	center = v_add((cy->pos), norm_mult);
	cam2cent = v_sub(origin, center);
	free(norm_mult);
	free(center);
	return (cam2cent);
}

void	do_set_normal(t_cylind *cy, t_point *origin, t_ic ic, t_vec *ray)
{
	if (just_get(ic.result) == just_get(ic.cap_hits))
		cy->cur_norm = v_mult(cy->norm, 1);
	else if (just_get(ic.result) == just_get
		(ic.tube_hits) && just_get(ic.result) > 0)
		set_tube_norm(get_surface(origin, ray,
				just_get(ic.tube_hits)), cy, ic.cap1.pos, ic.m1);
}

t_hit	inter_cylind(t_point *origin, t_vec *ray, t_cylind *cy, int set_normal)
{
	t_ic	ic;

	ic.cam2cent = calc_cam2cent(origin, cy);
	ic.tube_hits = solve_quad(ray, cy, ic.cam2cent);
	ic.m1 = calc_m(cy, ic.tube_hits, ic.cam2cent, ray);
	if (ic.m1 <= 0 && ic.m1 >= -cy->height)
		ic.result.a = just_get(ic.tube_hits);
	else
		ic.result.a = -1;
	ic.point1 = v_mult(cy->norm, cy->height / 2);
	v_add_inplace(ic.point1, cy->pos);
	ic.point2 = v_mult(cy->norm, -cy->height / 2);
	v_add_inplace(ic.point2, cy->pos);
	ic.cap1 = new_plane(ic.point1, cy->norm, cy->color);
	ic.cap2 = new_plane(ic.point2, cy->norm, cy->color);
	ic.cap_hits.a = inter_disk(origin, ray, &ic.cap1, cy->rad);
	ic.cap_hits.b = inter_disk(origin, ray, &ic.cap2, cy->rad);
	ic.result.b = get_positive(ic.cap_hits);
	if (set_normal)
		do_set_normal(cy, origin, ic, ray);
	free4(ic.cam2cent, ic.point1, ic.point2, NULL);
	return (ic.result);
}
