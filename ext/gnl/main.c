#include <stdio.h>
#include <string.h>
#include "get_next_line.h"
# include <fcntl.h>

int check(int res)
{
	return res;
}
int main()
{
	char *art = "\n\
               )                      )    (                \n\
 (  (    (  ( /(            (    ) ( /(    )\\(          (   \n\
 )\\))(  ))\\ )\\())    (     ))\\( /( )\\())  ((_)\\  (     ))\\  \n\
((_))\\ /((_|_))/     )\\ ) /((_)\\()|_))/    _((_) )\\ ) /((_) \n\
 (()(_|_)) | |_     _(_/((_))((_)\\| |_    | |(_)_(_/((_))   \n\
/ _` |/ -_)|  _|   | ' \\)) -_) \\ /|  _|   | || | ' \\)) -_)  \n\
\\__, |\\___| \\__|___|_||_|\\___/_\\_\\ \\__|___|_||_|_||_|\\___|  \n\
|___/         |_____|                |_____|                \n\
";

	printf("%s", art);
	printf("BUFFER_SIZE =>\t[%u]\n", BUFFER_SIZE);

	int fd;
	char *line;
	int ret;
	/* char *s; */
	/* line = (char *)ft_calloc(sizeof(char), 1); */

	/* fd = open("./texts/game.txt", O_RDONLY); */
	/* fd = open("./texts/among.txt", O_RDONLY); */
	/* fd = open("./texts/null.txt", O_RDONLY); */
	/* fd = open("./texts/test_file9", O_RDONLY); */
	fd = open("./text.txt", O_RDONLY);
	/* fd = open("/media/linux_data/data/work/2_ecole/tests/1_gnl/gnlTester/gnlTester/files/big_line_no_nl", O_RDONLY); */
	/* fd = open("/media/linux_data/data/work/2_ecole/tests/1_gnl/gnlTester/gnlTester/files/big_line_with_nl", O_RDONLY); */
	/* fd = 1000; */
	/* fd = -1; */

	/* line = NULL; */
	/* s = NULL; */
	/* int r = -1; */
	
	/* int gnlReturn = get_next_line(fd, &line); */
	/* printf("check -> %d\n", check(r == gnlReturn && (s == NULL ? line == NULL : !strcmp(line, s)))); */
	/* if (gnlReturn == 1) */
	/* 	free(line); */

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

	return 0;
}
