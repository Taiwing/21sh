#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*cwd;

	if (argc < 2)
		return (1);
	cwd = getcwd(NULL, 0);
	printf("current directory: %s\n", cwd);
	free(cwd);
	printf("trying to change working directory to '%s' ...\n", argv[1]);
	if (!chdir(argv[1]))
	{
		cwd = getcwd(NULL, 0);
		printf("current directory: %s\n", cwd);
		free(cwd);
	}
	else
	{
		perror("chdir");
		return (1);
	}
	return (0);
}
