/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:36 by riporth           #+#    #+#             */
/*   Updated: 2023/11/18 14:31:20 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_len(long tmp)
{
	int	i;

	i = 1;
	while (tmp >= 10)
	{
		i++;
		tmp = tmp / 10;
	}
	return (i);
}

char	*ft_itoa_whi(char *ret, int n, int len, long tmp)
{
	while (len > 0)
	{
		len--;
		ret[len + n] = ('0' + (tmp % 10));
		tmp = tmp / 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		len;
	long	tmp;
	int		i;
	char	*ret;

	i = 0;
	tmp = (long) n;
	if (tmp < 0)
	{
		tmp = -tmp;
		i = 1;
	}
	len = ft_itoa_len(tmp);
	ret = (char *)malloc(sizeof(char) * (len + i + 1));
	if (!ret)
		return (NULL);
	ret[len + i] = '\0';
	ret = ft_itoa_whi(ret, i, len, tmp);
	if (i == 1)
		ret[0] = '-';
	return (ret);
}
