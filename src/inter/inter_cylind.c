#include "minirt.h"

double	inter_disk(t_point *origin, t_vec *ray, t_plane *plane, double rad)
{
	double plane_hit;
	t_point *surface_point;
	t_vec *v;
	double d2;

	plane_hit = inter_plane(origin, ray, plane);
	if (plane_hit > 0)
	{
		surface_point = v_mult(ray, plane_hit);
		v_add_inplace(surface_point, origin);
		v = v_sub(surface_point, plane->pos);
		d2 = v_dot_product(v, v);
		if (sqrt(d2) <= rad)
			return (plane_hit);
	}
	return (-1);

}

void	set_tube_norm(t_point *surface_point, t_cylind *cy, t_point *cap_pos, double m)
{
	t_point *center;

	center = v_add(cap_pos, v_mult(cy->norm, m));
	cy->cur_norm = v_sub(surface_point, center);
	v_norm_inplace(cy->cur_norm);
	free(center);
}

t_point *get_surface(t_point *origin, t_vec *ray, double len)
{
	t_point *surface_point;

	surface_point = v_mult(ray, len);
	v_add_inplace(surface_point, origin);
	return (surface_point);
}

t_hit solve_quad(t_vec *ray, t_cylind *cy, t_vec *cam2cent)
{
	t_quad quad;

	quad.a = v_dot_product(ray, ray) - pow(v_dot_product(ray, cy->norm), 2);
	quad.b = v_dot_product(ray, cam2cent) - v_dot_product(ray, cy->norm) *
		v_dot_product(cam2cent, cy->norm);
	quad.c = v_dot_product(cam2cent, cam2cent) - pow(v_dot_product(cam2cent, cy->norm), 2) 
		- pow(cy->rad, 2);
	quad.b = quad.b * 2.0;
	quad.discr = (quad.b * quad.b) - (4 * quad.a * quad.c);
	if (quad.discr < 0)
		return (h_new(0, 0));
	return (h_new(
				(-quad.b - sqrt(quad.discr)) / (2 * quad.a),
				(-quad.b + sqrt(quad.discr)) / (2 * quad.a)
				));
}

t_hit	inter_cylind(t_point *origin, t_vec *ray, t_cylind *cy)
{
	t_hit tube_hits;
	t_hit cap_hits;
	t_hit result;
	t_vec *cam2cent;
	double m1;
	t_plane cap1;
	t_plane cap2;
	
	cam2cent = v_sub(origin, v_add((cy->pos), v_mult(cy->norm, cy->height / 2)));
	tube_hits = solve_quad(ray, cy, cam2cent);
	m1 = v_dot_product(ray, v_mult(cy->norm, get_positive(tube_hits))) + v_dot_product(cam2cent, cy->norm);
	if (m1 <= 0 && m1 >= -cy->height)
		result.a = just_get(tube_hits);
	else
		result.a = -1;
	cap1 = new_plane(v_add(cy->pos, v_mult(cy->norm, cy->height / 2)), cy->norm, cy->color);
	cap2 = new_plane(v_add(cy->pos, v_mult(cy->norm, -cy->height / 2)), cy->norm, cy->color);
	cap_hits.a = inter_disk(origin, ray, &cap1, cy->rad);
	cap_hits.b = inter_disk(origin, ray, &cap2, cy->rad);
	result.b = get_positive(cap_hits);
	if (just_get(result) == just_get(cap_hits))
		cy->cur_norm = v_mult(cy->norm, 1);
	else if (just_get(result) == just_get(tube_hits) && just_get(result) > 0)
		set_tube_norm(get_surface(origin, ray, just_get(tube_hits)), cy, cap1.pos, m1);
	else
		cy->cur_norm = NULL;

	return (result);
}
