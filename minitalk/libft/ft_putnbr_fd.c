/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:59:34 by riporth           #+#    #+#             */
/*   Updated: 2023/11/16 12:00:14 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_loop(unsigned int num, int fd)
{
	int		mod;

	if (num > 0)
	{
		mod = num % 10 + 48;
		num = num / 10;
		ft_loop(num, fd);
		write(fd, &mod, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
		num = n * (-1);
	else
		num = (unsigned int)n;
	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
		write(fd, "-", 1);
	ft_loop(num, fd);
}
