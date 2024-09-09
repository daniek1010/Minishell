/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:00:57 by riporth           #+#    #+#             */
/*   Updated: 2023/12/01 16:08:33 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printchar(int c)
{
	return (write (1, &c, 1));
}

int	printstr(char *chr)
{
	int	ct;
	int	i;

	i = 0;
	ct = 0;
	if (!chr)
		return (write (1, "(null)", 6));
	while (chr[i])
	{
		ct += write (1, &chr[i], 1);
		i++;
	}
	return (ct);
}

int	printaddr(unsigned long long int n, int ct)
{
	int		last_digit;

	if (ct == 0)
		ct += write(1, "0x", 2);
	if (n > 15)
	{
		ct = printaddr(n / 16, ct);
	}
	last_digit = n % 16;
	ct += write(1, &"0123456789abcdef"[last_digit], 1);
	return (ct);
}
