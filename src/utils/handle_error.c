#include "minirt.h"

void	handle_error(int code, int line)
{
	char	*msg;

	msg = NULL;
	if (code == ERR_ALLOC)
		msg = "Allocation error!";
	else if (code == ERR_LIST)
		msg = "List error";
	else if (code == ERR_ARG)
		msg = "Wrong amount of arguments!";
	else if (code == ERR_SUBNORM)
		msg = "Vector provided is not normal!";
	else if (code == ERR_NEG)
		msg = "Unexpected negative value.";
	else if (code == ERR_FILE)
		msg = "Cannot open/create file.";
	else if (code == ERR_TOKENS)
		msg = "Incorrect amount of tokens on line.";
	else if (code == ERR_RLINE)
		msg = "Incorrect amount of R lines.";
	else if (code == ERR_AMBLINE)
		msg = "Incorrect amount of A lines.";
	else
		msg = "Undefined";
	ft_putstr_fd("Error! 😰\n", 2);
	if (line > 0)
	{
		ft_putstr_fd("On line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putendl_fd("", 2);
	}
	ft_putstr_fd("[x] Error code => ", 2);
	ft_putnbr_fd(code, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	exit(code);
}
