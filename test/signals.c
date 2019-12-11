#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <signal.h> 
#include <unistd.h> 

pid_t pid; 
int counter = 0; 
void handler1(int sig) 
{
	(void)sig;
	counter++; 
	printf("counter = %d\n", counter); 
	/* Flushes the printed string to stdout */
	fflush(stdout); 
	kill(pid, SIGUSR1); 
} 
void handler2(int sig) 
{ 
	(void)sig;
	counter += 3; 
	printf("counter = %d\n", counter); 
	fflush(stdout); 
	exit(0);
} 

int main(void) 
{ 
	pid_t p; 
	int status; 

	signal(SIGUSR1, handler1); 
	if ((pid = fork()) == 0) 
	{ 
		signal(SIGUSR1, handler2); 
		kill(getppid(), SIGUSR1);
		while(1) ; 
		printf("DOES IT PRINT ?\n");
		fflush(stdout); 
	} 
	if ((p = wait(&status)) > 0) 
	{ 
		counter += 4; 
		printf("counter = %d\n", counter); 
		fflush(stdout); 
	} 
	return (0);
} 
