#include "minirt.h"

int	split_len(char **data)
{
	int	count;

	if (!data || !(*data))
		handle_error(-10, -1);
	count = 0;
	while (data[count])
	{
		count++;
	}
	return (count);
}
