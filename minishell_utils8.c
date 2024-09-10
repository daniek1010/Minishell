/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:10:36 by riporth           #+#    #+#             */
/*   Updated: 2024/09/10 22:14:47 by danevans         ###   ########.fr       */
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

int	print_error(char *str_i, char *str_0)
{
	int	i;

	if (str_i[0] == '=' || (str_i[0] >= '0' && str_i[0] <= '9'))
	{
		printf("minishell: %s:\'%s\': not a valid identifier\n",
			str_0, str_i);
		return (1);
	}
	i = 0;
	while (str_i[i] != '\0' && str_i[i] != '=')
	{
		if (!ft_isalnum(str_i[i]))
		{
			printf("minishell: %s:\'%s\': not a valid identifier\n",
				str_0, str_i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_filename(char *token_array[], int start)
{
	if (is_redir(token_array, start))
		return (0);
	else if (ft_strcmp(token_array[start], "|") == 0
		|| ft_strcmp(token_array[start], "*") == 0
		|| ft_strcmp(token_array[start], "?") == 0)
		return (0);
	return (1);
}
