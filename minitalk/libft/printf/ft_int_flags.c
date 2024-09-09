/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:47:44 by riporth           #+#    #+#             */
/*   Updated: 2023/12/01 16:08:09 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printint(int n, int ct)
{
	char	last_digit;

	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		ct += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ct = printint(n / 10, ct);
	}
	last_digit = n % 10 + '0';
	ct += write(1, &last_digit, 1);
	return (ct);
}

int	printuint(unsigned int n, int ct)
{
	char		last_digit;

	if (n > 9)
	{
		ct = printint(n / 10, ct);
	}
	last_digit = n % 10 + '0';
	ct += write(1, &last_digit, 1);
	return (ct);
}

int	printhex(unsigned int n, int ct)
{
	int		last_digit;

	if (n > 15)
	{
		ct = printhex(n / 16, ct);
	}
	last_digit = n % 16;
	ct += write(1, &"0123456789abcdef"[last_digit], 1);
	return (ct);
}

int	printhexu(unsigned int n, int ct)
{
	int		last_digit;

	if (n > 15)
	{
		ct = printhexu(n / 16, ct);
	}
	last_digit = n % 16;
	ct += write(1, &"0123456789ABCDEF"[last_digit], 1);
	return (ct);
}
