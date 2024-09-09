/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:48 by riporth           #+#    #+#             */
/*   Updated: 2024/01/24 18:21:39 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

static void	print_server(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

void	ft_nl(int adress)
{
	int		i;
	char	c;

	i = 8;
	c = '\n';
	while (i--)
	{
		if (c >> i & 1)
			kill(adress, SIGUSR2);
		else
			kill(adress, SIGUSR1);
		usleep(10);
	}
}

static void	ft_send(int adress, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(adress, SIGUSR2);
			else
				kill(adress, SIGUSR1);
			usleep(10);
		}
	}
	ft_nl(adress);
	i = 8;
	while (i--)
	{
		kill(adress, SIGUSR1);
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]) + 1, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, print_server);
	signal(SIGUSR2, print_server);
	ft_send(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
