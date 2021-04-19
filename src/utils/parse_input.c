#include "minirt.h"

void parse_input(char *file)
{
	int fd;
	char *line;
	int ret;
	fd = open(file, O_RDONLY);

	while ((ret = get_next_line(fd, &line)) == 1)
	{
		/* printf("the line is =>[%s]\n", line); */
		printf("%s\n", line);
		free(line);
	}
	if (!ret)
		free(line);
	printf("gnl returned -> [%d]\n", ret);

	close(fd);
}
