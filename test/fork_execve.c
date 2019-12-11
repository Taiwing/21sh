#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	pid_t	cp;
	int		ret;

	if (argc < 2)
		return (1);
	cp = 0;
	ret = 0;
	printf("trying to exec '%s' ...\n", argv[1]);
	if ((cp = fork()) == -1)
	{
		perror("fork");
		return (1);
	}
	else if (!cp)
	{
		if (execve(argv[1], argv + 1, NULL) == -1)
			perror("execve");
		printf("gagagagaaaaah\n");
		return (1);
	}
	else if (wait(&ret) == -1)
	{
		perror("wait");
		return (1);
	}
	printf("child pid: %d\n", cp);
	printf("parent pid: %d\n", getpid());
	return (0);
}
