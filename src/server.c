/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:26:08 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/14 15:59:03 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <string.h>

//server recieve msg and print

void	bits_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c <<= 1;
}

void	handle_signal(int signum, siginfo_t *info, void *params)
{
	static int		i;
	static int		pid;
	static char		c;

	(void)params;
	if (pid == 0)
		pid = info->si_pid;
	bits_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	signals;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART | SA_SIGINFO;
	signals.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &signals, NULL);
	sigaction(SIGUSR2, &signals, NULL);
	while (1)
		pause();
	return (0);
}
