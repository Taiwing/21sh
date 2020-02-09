#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>

#define SHE_BANG	"#!/usr/bin/env bash\n"	//NICE
#define FILE_NAME	"crash_word_limit"
#define COMMAND_STRING	"echo "
//#define BASE_LEN	(UINT_MAX / 2)
#define BASE_LEN	9192
#define MAX_ARG		(BASE_LEN / 2)

uintmax_t	atouimax(const char *nptr)
{
	uintmax_t	nb = 0;

	while (*nptr == 32 || (*nptr > 8 && *nptr < 14)) ++nptr;
	while (*nptr > 47 && *nptr < 58) nb = (nb * 10) + ((*nptr++) - 48);
	return (nb);
}

int		main(int argc, char **argv)
{
	int		fd;
	uintmax_t	nb_args;
	char		to_write[BASE_LEN];

	if (argc < 2 || !(nb_args = atouimax(argv[1])))
	{
		dprintf(2, "error: wrong arguments\n");
		return (1);
	}
	if ((fd = open(FILE_NAME, O_CREAT | O_TRUNC | O_WRONLY, 0755)) < 0)
	{
		perror("open");
		return (1);
	}
	memset((void *)to_write, ' ', BASE_LEN);
	for (uintmax_t i = 0; i < MAX_ARG; ++i)
		to_write[i*2+1] = 'o';
	write(fd, SHE_BANG, strlen(SHE_BANG));
	write(fd, COMMAND_STRING, strlen(COMMAND_STRING));
	while (nb_args > MAX_ARG)
	{
		write(fd, to_write, BASE_LEN);
		nb_args -= MAX_ARG;
	}
	write(fd, to_write, nb_args * 2);
	write(fd, "\n", 1);
	close(fd);
	return (0);
}
