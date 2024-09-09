/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:52 by riporth           #+#    #+#             */
/*   Updated: 2024/01/25 11:46:21 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

static void	print_client(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			return_adress = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!return_adress)
		return_adress = info->si_pid;
	c |= (sig == SIGUSR2);
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(return_adress, SIGUSR2);
			return_adress = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(return_adress, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	signal_action;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal_action.sa_sigaction = print_client;
	signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_action, 0);
	sigaction(SIGUSR2, &signal_action, 0);
	while (1)
		pause();
	return (0);
}
