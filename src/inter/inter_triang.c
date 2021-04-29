#include "minirt.h"

double	inter_triang(t_point *origin, t_vec *ray, t_triang *tri)
{
	t_vec		*edge1;
	t_vec		*edge2;
	t_moller	mol;

	edge1 = v_sub(tri->b, tri->a);
	edge2 = v_sub(tri->c, tri->a);
	mol.pvec = v_cross(ray, edge2);
	mol.determ = v_dot_product(edge1, mol.pvec);
	/* if (determ > -FLT_EPSILON && determ < FLT_EPSILON) */
	/* 	return (0); */
	if (v_dot_product(tri->norm, ray) == 0)
		return (0);
	mol.tvec = v_sub(origin, tri->a);
	mol.u = v_dot_product(mol.tvec, mol.pvec) / mol.determ;
	mol.qvec = v_cross(mol.tvec, edge1);
	mol.v = v_dot_product(ray, mol.qvec) / mol.determ;
	if (mol.u < 0.0 || mol.u > 1.0 || mol.v < 0.0 || mol.u + mol.v > 1.0)
		return (0);
	mol.t = v_dot_product(edge2, mol.qvec) / mol.determ;
	if (mol.t > FLT_EPSILON)
		return (v_dot_product(edge2, mol.qvec) / mol.determ);
	return (0);
}
