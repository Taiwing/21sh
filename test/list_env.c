#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	while (*env)
		printf("%s\n", *env++);
	return (0);
}
