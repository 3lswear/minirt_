#include "minirt.h"

float get_positive(t_hit hit)
{
	if ((hit.a * hit.b > 0) && hit.a > 0)
	{
		if (hit.a > hit.b)
			return (hit.b);
		else
			return (hit.a);
	}
	else if (hit.a * hit.b < 0)
	{
		if (hit.a > hit.b)
			return (hit.a);
		else
			return (hit.b);
	}
	else
		return (0);
}

float just_get(t_hit hit)
{
	/* if (hit.a * hit.b > 0.0) */
		if (hit.a > hit.b)
			return (hit.b);
		else
			return (hit.a);
	/* else */
	/* 	if (hit.a > 0.0) */
	/* 		return (hit.a); */
	/* 	else */
	/* 		return (hit.b); */
}
