#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PID_SIZE 64

static int	exec_in_fork(int *in_tube, int *out_tube, int proc_id)
{
	pid_t	cp;
	char	pid[PID_SIZE];

	cp = 0;
	ret = 0;
	if ((cp = fork()) == -1)
	{
		perror("fork");
		return (1);
	}
	else if (!cp)
	{
		snprintf(pid, PID_SIZE, "%d", getpid());
		exit(0);
	}
	else if (wait(NULL) == -1)
	{
		perror("wait");
		return (1);
	}
	return (0);
}

static int	*init_tubes(int proc_count)
{
	int	*tubes;

	tubes = NULL;	
	if (proc_count > 1)
		tubes = (int *)malloc((proc_count - 1) * 2 * sizeof(int));
	if (tubes)
	{
		for (int i = 0, int *ptr = tubes; i < proc_count - 1; ++i, ptr += 2)
		{
			if (pipe(ptr))
			{
				perror("pipe");
				free(tubes);
			}
		}
	}
	return (tubes);
}

int	main(int argc, char **argv)
{
	int		*tubes;
	int		proc_count;

	proc_count = 1;
	if (argc < 2)
		fprintf(stderr, "%s: error: not enough arguments\n", argv[0]);
	else if ((proc_count = atoi(argv[1])) <= 0)
		fprintf(stderr, "%s: error: process count value is\
			inferior or equal to 0\n", argv[0]);
	else if ((tubes = init_tubes(proc_count)) || proc_count < 2)
	{
		for (int i = 0; i < proc_count; ++i)
			exec_in_fork(i ? tubes + (i - 1) * 2 : NULL, tubes + i * 2, i);
		free(tubes);
	}
	return (proc_count);
}
