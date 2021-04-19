#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include "libft.h"
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#include <ctype.h>

	/* size_t	ft_lg(int n) */
	/* { */
	/* 	size_t result; */

	/* 	result = 0; */
	/* 	while ((n = n / 10)) */
	/* 		result++; */
	/* 	return (result); */
	/* } */
char mapi_func(unsigned int num, char c)
{
	(void)num;
	return (ft_toupper(c));
}

int main()
{

/* 	char *le_title ="                  __           ______     _____.__                   __                   __         ._._._.\n\ */
/* 	  _______/  |________ /  __  \\  _/ ____\\__|______   ____   _/  |_  ____   _______/  |_  _____| | | |\n\ */
/* 	 /  ___/\\   __\\_  __ \\>      <  \\   __\\|  \\_  __ \\_/ __ \\  \\   __\\/ __ \\ /  ___/\\   __\\/  ___/ | | |\n\ */
/* 	 \\___ \\  |  |  |  | \\/   --   \\  |  |  |  ||  | \\/\\  ___/   |  | \\  ___/ \\___ \\  |  |  \\___ \\ \\|\\|\\|\n\ */
/* 	/____  > |__|  |__|  \\______  /  |__|  |__||__|    \\___  >  |__|  \\___  >____  > |__| /____  >______\n\ */
/*     	     \\/                     \\/                         \\/             \\/     \\/            \\/ \\/\\/\\/"; */

	char *le_title2="\n\
	   /$$                           /$$     /$$                           /$$                     /$$                 /$$ /$$ /$$\n\
	  | $$                          | $$    |__/                          | $$                    | $$                | $$| $$| $$\n\
	 /$$$$$$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$ /$$$$$$$   /$$$$$$       | $$  /$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$$| $$| $$| $$\n\
	|_  $$_/   /$$__  $$ /$$_____/|_  $$_/  | $$| $$__  $$ /$$__  $$      | $$ /$$__  $$ |____  $$| $$  /$$/ /$$_____/| $$| $$| $$\n\
	  | $$    | $$$$$$$$|  $$$$$$   | $$    | $$| $$  \\ $$| $$  \\ $$      | $$| $$$$$$$$  /$$$$$$$| $$$$$$/ |  $$$$$$ |__/|__/|__/\n\
	  | $$ /$$| $$_____/ \\____  $$  | $$ /$$| $$| $$  | $$| $$  | $$      | $$| $$_____/ /$$__  $$| $$_  $$  \\____  $$            \n\
	  |  $$$$/|  $$$$$$$ /$$$$$$$/  |  $$$$/| $$| $$  | $$|  $$$$$$$      | $$|  $$$$$$$|  $$$$$$$| $$ \\  $$ /$$$$$$$/ /$$ /$$ /$$\n\
	   \\___/   \\_______/|_______/    \\___/  |__/|__/  |__/ \\____  $$      |__/ \\_______/ \\_______/|__/  \\__/|_______/ |__/|__/|__/\n\
                                                               /$$  \\ $$                                                            \n\
                                                              |  $$$$$$/                                                            \n\
                                                               \\______/                                                             \n\
\n";
	printf("%s\n", le_title2);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> SPLIT <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);

	char *split_str = "      split       this for   me  !       ";
	char sep = ' ';
	char **split_result;
	int splt_i = 0;
	split_result = ft_split(split_str, sep);
	if (split_result)
	{
		while (split_result[splt_i])
		{
			printf("[%s]\n", split_result[splt_i]);
			splt_i++;
		}
	}

	splt_i = 0;
	if (split_result)
	{
		printf("result is a valid ptr!!\n");
		while (split_result[splt_i])
		{
			printf("freeing block\t%d\n", splt_i);
			free(split_result[splt_i]);
			splt_i++;
		}
	free (split_result);
	}
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> CALLOC <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);

	char *calloc_result;
	calloc_result = calloc(21, sizeof(char));
	strlcpy(calloc_result, "i am a string haiii", 21);
	if (calloc_result)
	{
		printf("calloc_result =>\t[%s]\n", calloc_result);
		free(calloc_result);
	}
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> ITOA <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *itoa_result;
	if ((itoa_result = ft_itoa(1354651848)))
	{
		printf("itoa_result =>\t[%s]\n", itoa_result);
		free(itoa_result);
	}
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> STRMAPI <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *mapi_string = "hi im a lowercase string";
	char *mapi_result;
	mapi_result= ft_strmapi(mapi_string, *mapi_func); 
	if (mapi_result)
	{
		printf("mapi_result =>\t[%s]\n", mapi_result);
		free(mapi_result);
	}

	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> STRTRIM <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *trim_str = "aaaaaaaaaaaaaaaaaaim screaming its very scaryaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char *trim_set = "a";
	char *trim_result;

	if ((trim_result = ft_strtrim(trim_str, trim_set)))
	{
		printf("trim_result =>\t[%s]\n", trim_result);
		free(trim_result);
	}

	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> STRJOIN <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *join_str1 = "hi my name is";
	char *join_str2 = " roma !!!!";
	char *join_result;
	if ((join_result = ft_strjoin(join_str1, join_str2)))
	{
		printf("join_result =>\t[%s]\n", join_result);
		free(join_result);
	}
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> SUBSTR <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *substr_str = "hello i am a very long string of which you need to find a substring";
	char *substr_result;

	if ((substr_result = ft_substr(substr_str, 0, 10)))
	{
		printf("substr_result =>\t[%s]\n", substr_result);
		free(substr_result);
	}
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("▓▓▓▓▓▓▓▓▓▓▓▓▓▓ |||> STRDUP <||| ▓▓▓▓▓▓▓▓▓▓▓▓▓▓", 1);
	ft_putchar_fd('\n', 1);
	char *dup_str = "hai i am a string to duplicate";
	char *dup_result;
	if ((dup_result = ft_strdup(dup_str)))
	{
		printf("dup_result =>\t[%s]\n", dup_result);
		free(dup_result);
	}
	return 0;
}
