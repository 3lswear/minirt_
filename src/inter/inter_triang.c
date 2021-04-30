#include "minirt.h"

int	free_moller(t_moller *mol)
{
	free(mol->pvec);
	free(mol->qvec);
	free(mol->tvec);
	return (1);
}

double	inter_triang(t_point *origin, t_vec *ray, t_triang *tri)
{
	t_moller	mol;
	double result;

	/* if (determ > -FLT_EPSILON && determ < FLT_EPSILON) */
	/* 	return (0); */
	if (v_dot_product(tri->norm, ray) == 0)
		return (0);
	mol.pvec = v_cross(ray, tri->edge2);
	mol.determ = v_dot_product(tri->edge1, mol.pvec);
	mol.tvec = v_sub(origin, tri->a);
	mol.u = v_dot_product(mol.tvec, mol.pvec) / mol.determ;
	mol.qvec = v_cross(mol.tvec, tri->edge1);
	mol.v = v_dot_product(ray, mol.qvec) / mol.determ;
	if ((mol.u < 0.0 || mol.u > 1.0 || mol.v < 0.0 || mol.u + mol.v > 1.0)
			&& (free_moller(&mol)))
		return (0);
	mol.t = v_dot_product(tri->edge2, mol.qvec) / mol.determ;
	result = v_dot_product(tri->edge2, mol.qvec) / mol.determ;
	free_moller(&mol);
	if (mol.t > FLT_EPSILON)
		return (result);
	return (0);
}
