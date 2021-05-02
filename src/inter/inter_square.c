#include "minirt.h"

double inter_square(t_point *origin, t_vec *ray, t_square *sq)
{


	t_triang t1;
	t_triang t2;

	t_hit hit;

	/* print_vec(a, "a pos "); */
	/* print_vec(b, "b pos "); */
	/* print_vec(c, "c pos "); */
	/* print_vec(d, "d pos "); */

	t1 = new_triang(sq->a, sq->b, sq->c, sq->color);
	t2 = new_triang(sq->a, sq->c, sq->d, sq->color);

	t1.norm = triang_get_norm(&t1);
	t2.norm = triang_get_norm(&t2);
	
	hit.a = inter_triang(origin, ray, &t1);
	hit.b = inter_triang(origin, ray, &t2);
	free(t1.norm);
	free(t2.norm);
	free(t1.edge1);
	free(t1.edge2);
	free(t2.edge1);
	free(t2.edge2);

	if (hit.a > 0)
		return (hit.a);
	else 
		return (hit.b);

	/* if (ray_len < 0) */
	/* 	return (ray_len); */
	/* return (0); */

}
