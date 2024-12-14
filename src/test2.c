#include "../inc/minitalk.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Function to append a character to a string
char	*charjoin(char *str, int c)
{
	char	*newstr;
	int		i = 0;

	// Handle NULL case for str
	int len = (str != NULL) ? strlen(str) : 0;
	newstr = malloc(len + 2); // +2 for the new character and null terminator
	if (!newstr)
		return (NULL);

	if (str)
	{
		while (str[i])
		{
			newstr[i] = str[i];
			i++;
		}
		free(str); // Free the old string
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	return (newstr);
}

// Signal handler
void	handle_signal(int signum)
{
	static int		count = 0;
	static int		save = 0;
	static char		*str = NULL;

	if (signum == SIGUSR1)
		save += 0;
	else if (signum == SIGUSR2)
		save += (1 << (7 - count));
	count++;
	if (count == 8)
	{
		str = charjoin(str, save);
		if (save == '\0')
		{
			write(1, str, strlen(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		count = 0;
		save = 0;
	}
}

int	main(void)
{
	struct sigaction	signals;

	// Print the PID
	printf("Server PID: %d\n", getpid());
	signals.sa_handler = handle_signal;
	signals.sa_flags = 0;
	sigemptyset(&signals.sa_mask);
	sigaction(SIGUSR1, &signals, NULL);
	sigaction(SIGUSR2, &signals, NULL);
	while (1)
		pause();
	return (0);
}
