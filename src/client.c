/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:26:14 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/14 16:41:16 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int	g_receiver;

void	handle_signal(int n, siginfo_t *info, void *params)
{
	static int	i;

	(void)params;
	(void)info;
	(void)n;
	g_receiver = 1;
	if (n == SIGUSR2)
		i++;
	else if (n == SIGUSR1)
		ft_printf("Num of bytes received -> %d\n", i / 8);
}

int	char_to_bits(char c, int pid)
{
	int	timeout;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		timeout = 0;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver == 0)
		{
			if (timeout == 50)
			{
				ft_putendl_fd("No response from server.", 1);
				exit(1);
			}
			timeout++;
			usleep(100);
		}
		g_receiver = 0;
		bit_index--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct sigaction	action;
	int					server_id;
	int					byte;

	if (ac != 3)
	{
		ft_printf("incorrect args: client requires only PID and message\n");
		exit(1);
	}
	byte = 0;
	server_id = ft_atoi(av[1]);
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART | SA_SIGINFO;
	action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (av[2][byte])
		char_to_bits(av[2][byte++], server_id);
	char_to_bits('\0', server_id);
	return (0);
}
