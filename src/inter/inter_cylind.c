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

t_hit	inter_cylind(t_point *origin, t_vec *ray, t_cylind *cy)
{
	t_hit tube_hits;
	double rad;
	double discr;
	double a;
	double b;
	double c;
	t_vec *cam2cent;
	double m1;
	double m2;
	t_hit cap_hits;
	t_plane cap1;
	t_plane cap2;
	t_hit result;

	t_color red;
	t_point *surface_point;

	t_point *center;

	red = new_color(255, 0, 0);
	rad = cy->diam / 2.0;
	/* cam2cent = v_sub(origin, cy->pos); */
	cam2cent = v_sub(origin, v_add((cy->pos), v_mult(cy->norm, cy->height / 2)));
	a = v_dot_product(ray, ray) - pow(v_dot_product(ray, cy->norm), 2);
	b = v_dot_product(ray, cam2cent) - v_dot_product(ray, cy->norm) *
		v_dot_product(cam2cent, cy->norm);
	c = v_dot_product(cam2cent, cam2cent) - pow(v_dot_product(cam2cent, cy->norm), 2) 
		- pow(rad, 2);
	b = b * 2.0;
	discr = (b * b) - (4 * a * c);
	if (discr < 0)
	{
		tube_hits.a = 0;
		tube_hits.b = 0;
		return (tube_hits);
	}
	tube_hits.a = (-b - sqrt(discr)) / (2 * a);
	tube_hits.b = (-b + sqrt(discr)) / (2 * a);
	
	m1 = v_dot_product(ray, v_mult(cy->norm, get_positive(tube_hits))) + v_dot_product(cam2cent, cy->norm);
	/* m1 = v_dot_product(ray, v_mult(cy->norm, tube_hits.a)) + v_dot_product(cam2cent, cy->norm); */
	/* m2 = v_dot_product(ray, v_mult(cy->norm, tube_hits.b)) + v_dot_product(cam2cent, cy->norm); */
	/* printf("positive tube_hits => %lf\n", get_positive(tube_hits)); */
	(void)m2;
	if (m1 <= 0 && m1 >= -cy->height)
	/* if ((m1 <= 0 && m1 >= -(cy->height)) || (m2 <= 0 && m2 >= -(cy->height))) */
	{
		result.a = just_get(tube_hits);
	}
	else
		result.a = -1;

	cap1 = new_plane(v_add(cy->pos, v_mult(cy->norm, cy->height / 2)), cy->norm, cy->color);
	cap2 = new_plane(v_add(cy->pos, v_mult(cy->norm, -cy->height / 2)), cy->norm, cy->color);
	/* print_vec(cap1.pos, "cap1 pos "); */
	/* print_vec(cap2.pos, "cap2 pos "); */
	/* print_vec(cap1.norm, "cap1 norm"); */
	/* cap_hits.a = inter_plane(origin, ray, &cap1); */
	/* cap_hits.b = inter_plane(origin, ray, &cap2); */
	cap_hits.a = inter_disk(origin, ray, &cap1, rad);
	cap_hits.b = inter_disk(origin, ray, &cap2, rad);
	/* printf("cap_hits.a => %lf\n", cap_hits.a); */
	/* printf("cap_hits.b => %lf\n", cap_hits.b); */
	result.b = get_positive(cap_hits);
	/* result.b = -1; */
	/* if (result.a != -1 && result.b != 0) */
	/* { */
	/* 	printf("result.a => %lf\n", result.a); */
	/* } */
	/* cy->cur_norm = v_mult(cy->norm, 1); */
	if (just_get(result) == just_get(cap_hits))
		cy->cur_norm = v_mult(cy->norm, 1);
	else if (just_get(result) == just_get(tube_hits) && just_get(result) > 0)
	{
		surface_point = v_mult(ray, get_positive(tube_hits));
		v_add_inplace(surface_point, origin);
		/* printf("norm is tube's\n"); */

		center = v_add(cap1.pos, v_mult(cy->norm, m1));
		/* v_sub_inplace(center, origin); */

		cy->cur_norm = v_sub(surface_point, center);
		v_norm_inplace(cy->cur_norm);

		/* print_vec(surface_point, "surface_point\t"); */
		print_vec(center, "center\t\t");
		/* printf("m1 is %lf\n", m1); */
	}
	else
		cy->cur_norm = NULL;

	/* if (result.b != 0) */
	/* 	printf("result.b => %lf\n", result.b); */
	/* printf("jopa\n"); */
	return (result);
}
