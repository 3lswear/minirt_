#include "minirt.h"


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