#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <strings.h>

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

int		sighand(int sig)
{
	static int	c = 0;

	if (sig == SIGINT)
		c = '\003';
	else if (sig == SIGHUP)
		c = '\032';
	else if (sig == SIGQUIT)
		c = '\034';
	else if (!sig)
		c = 0;
	else if (sig == 42)
		return (c);
	return (0);
}

void	reset_input_mode (void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void	set_input_mode (void)
{
	struct termios tattr;

	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO))
	{
		fprintf (stderr, "Not a terminal.\n");
		exit (EXIT_FAILURE);
	}

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr (STDIN_FILENO, &saved_attributes);
	atexit (reset_input_mode);

	/* Set the funny terminal modes. */
	tcgetattr (STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO|ISIG); /* Clear ICANON and ECHO and ISIG. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int	main (void)
{
	char	c[16];
	int		rd;

	set_input_mode ();

	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, (void(*)(int))sighand);
	signal(SIGQUIT, (void(*)(int))sighand);

	while (1)
	{
		bzero(c, 16);
		if ((rd = read (STDIN_FILENO, c, 16)) == -1)
			break ;
		else if (rd > 1)
		{
			printf("special char:");
			for (int i = 0; i < rd; ++i)
				printf(" %d", (int)c[i]);
			printf("\n");
			fflush(stdout);
		}
		/*if (sighand(42))
		{
			printf("SIGNAL: %o\n", (unsigned int)sighand(42));
			fflush(stdout);
			sighand(0);
		}*/
		else if (*c == '\003')		/* C-c */
		{
			printf("Ctrl + C\n");
			fflush(stdout);
		}
		else if (*c == '\004')		/* C-d */
			break;
		else if (*c == '\032')		/* C-z */
		{
			printf("Ctrl + Z\n");
			fflush(stdout);
		}
		else if (*c == '\034')		/* C-\ */
		{
			printf("Ctrl + \\\n");
			fflush(stdout);
		}
		else if (*c == '\177')		/*backspace*/
		{
			putchar('\010');
			putchar(' ');
			putchar('\010');
			fflush(stdout);
		}
		else
		{
			putchar (*c);
			printf("\nascii value: %d\n", (int)*c);
			fflush(stdout);
		}
	}

	return EXIT_SUCCESS;
}
