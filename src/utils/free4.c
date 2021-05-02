#include "minirt.h"

int	free4(void *a, void *b, void *c, void *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
	return (1);
}
