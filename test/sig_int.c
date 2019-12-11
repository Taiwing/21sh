#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	signal_handler(int sig)
{
	(void)sig;
	printf("HOLY SHIT, WE GOTTA GET THE FUCK OUT OF HERE !!!\n");
	fflush(stdout);
}

int	main(int argc, char **argv)
{
	pid_t	cp;
	int		ret;

	if (argc < 2)
		return (1);
	ret = 0;
	printf("trying to exec '%s' ...\n", argv[1]);
	signal(SIGINT, signal_handler);	/*SIGINT reloads prompt in minishell*/
	if ((cp = fork()) == -1)
	{
		perror("fork");
		return (1);
	}
	else if (!cp)
	{
		if ((ret = execve(argv[1], argv + 1, NULL)) == -1)
			perror("execve");
		return (ret);
	}
	else if (wait(&ret) == -1)
	{
		perror("wait");
		return (1);
	}
	printf("child process returned: %d\n", ret);
	printf("child pid: %d\n", cp);
	printf("parent pid: %d\n", getpid());
	fflush(stdout);
	return (0);
}
