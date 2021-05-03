#include "minirt.h"

t_obj	*new_object(int type, t_object *object)
{
	t_obj	*result;

	(void)object;
	result = malloc(sizeof(t_obj));
	result->type = type;
	return (result);
}
