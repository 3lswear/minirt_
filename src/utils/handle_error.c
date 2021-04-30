#include "minirt.h"

void handle_error(int code)
{
	char *msg;

	msg = NULL;
	if (code == ERR_ALLOC)
		msg = "Allocation error!";
	else if (code == ERR_LIST)
		msg = "List error";
	else if (code == ERR_ARG)
		msg = "Wrong amount of arguments!";
	else if (code == ERR_SUBNORM)
		msg = "Vector provided is not normal!";
	else
		msg = "idk 🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔";

	ft_putstr_fd("😰😰😰😰 uh oh, something bad happened!!!!!!!! 😰😰😰😰\n", 2);
	ft_putstr_fd("[x] Error code => ", 2);
	ft_putnbr_fd(code, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	
	exit(code);
}
