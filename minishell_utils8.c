/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:36 by riporth           #+#    #+#             */
/*   Updated: 2024/09/10 14:11:30 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	int			n;
	long long	tmp;
	int			i;

	n = 1;
	i = 0;
	tmp = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11 || str[i] == 12
		|| str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		tmp = tmp * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(tmp * n));
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
