/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:37:43 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/14 05:45:02 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <signal.h>

// void handle_sig(int sig)
// {
// 	printf("Got signal %d\n", sig);
// 	//exit(EXIT_FAILURE);
// }

// int	main(void)
// {
// 	struct sigaction action;
// 	action.sa_handler = handle_sig;
// 	sigemptyset(&action.sa_mask);
// 	action.sa_flags = 0;
	
// 	sigaction(SIGINT, &action, NULL);
	
// 	while (1) {
// 		printf("on process %d\n", getpid());
// 		sleep(3);
// 	}
// 	// signal(SIGINT, handle_sig);
// 	// signal(SIGTERM, handle_sig);
// 	// while(1)
// 	// {
// 	// 	printf("on process %d\n", getpid());
// 	// 	sleep(3);
// 	// }
// 	return 0;
// }

//#include "minitalk.h"
#include <string.h>

int	ft_recursive_power(int nb, int power)
{
	int	res;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		res = nb * ft_recursive_power(nb, power - 1);
		return (res);
	}
}

char	*letter_to_string(char const *s1, char const letter)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc((strlen(s1) + 2) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	tab[j++] = letter;
	tab[j] = 0;
	free ((void *)(s1));
	return (tab);
}

void	signal_handler(int signum)
{
	static int	counter = 0;
	static int	result = 0;
	static int	len = 0;
	static char	*final;

	if (!final)
		final = strdup("");
	if (signum == SIGUSR1)
		result = result + 0;
	else if (signum == SIGUSR2)
		result = result + (1 * ft_recursive_power(2, 7 - counter));
	counter++;
	if (counter == 8)
	{
		final = letter_to_string(final, result);
		if (result == '\0')
		{
			printf("%s\n", final);
			final = NULL;
		}
		counter = 0;
		result = 0;
		len += 1;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	printf("Welcome to lfabbian's server :-)\n");
	printf("Server's PID: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		usleep(50);
}