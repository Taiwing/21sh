#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <term.h>
#include <termios.h>

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

void	reset_input_mode (void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void	set_input_mode (void)
{
	struct termios tattr;
//	char	*amstr;
//	char	*name_term;


	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO))
	{
		fprintf (stderr, "Not a terminal.\n");
		exit (EXIT_FAILURE);
	}

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr(STDIN_FILENO, &saved_attributes);
	atexit(reset_input_mode);

/*	if (!(name_term = getenv("TERM")))
		exit(EXIT_FAILURE);
	printf("terminal name: %s\n", name_term);
	if (!tgetent(NULL, name_term))
		exit(EXIT_FAILURE);
	amstr = tgetstr("am", NULL);
	printf("%s", amstr);
	fflush(stdout);*/

	/* Set the funny terminal modes. */
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

int	main (void)
{
	unsigned char	ans[16];
	char			c[8];
	int				rd;
	int				i;
	size_t			l;
	
	set_input_mode();
	i = 0;
	while(1)
	{
		bzero(c, 8);
		rd = read(STDIN_FILENO, c, 8);
		write(1, c, rd);
		if (++i == 12)
		{
			i = 0;
			write(0, "\x1B[6n", 4);
			l = 0;
			while (l < 15 && read(0, ans + l, 1) == 1)
				if (ans[l++] == 'R')
					break ;
			ans[l] = 0;
			printf ("\nAnswerback = \"");
			for (size_t i = 0; i < l; ++ i)
				if (ans[i] < ' ' || '~' < ans[i])
					printf ("\\x%02X", (unsigned char)ans[i]);
				else
			        printf ("%c", ans[i]);
			 printf ("\"\r\n");
		}
	}
	return EXIT_SUCCESS;
}
