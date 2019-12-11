#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	size = 0;

	for (int i = 10; i > -1; --i)
	{
		if (size)
		{
			printf("\r%*s", size - 1, "");
			fflush(stdout);
		}
		size = printf("\rValue of i is: %d", i);
		fflush(stdout);
		if (i == 5)
			write(0, "yoooo", 5);
		sleep(1);
	}
	printf("\n");
	return (0);
}
