/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:39:45 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 20:24:48 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	long			num;

	len = ft_len(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num)
	{
		str[len--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

int	alpha_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9'))
		{
			if ((str[0] >= '0' && str[0] <= '9'))
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
}

void	ft_check_builtin(t_command *command, t_infos *tokens)
{
	tokens->e_code = 0;
	if (ft_strcmp("echo", command->name) == 0)
		tokens->e_code = builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		tokens->e_code = builtin_env(tokens->envp);
	else if (ft_strcmp("export", command->name) == 0)
		tokens->e_code = builtin_export(tokens->envp, command->args);
	else if (ft_strcmp("unset", command->name) == 0)
		tokens->e_code = builtin_unset(tokens->envp, command->args);
	else if (ft_strcmp("cd", command->name) == 0)
		tokens->e_code = builtin_cd(tokens->envp, command->args[1]);
	else if (ft_strcmp("pwd", command->name) == 0)
		tokens->e_code = builtin_pwd();
	else if (ft_strcmp("exit", command->name) == 0)
	{
		ft_putendl_fd("exiting", STDOUT_FILENO);
		tokens->e_code = -5;
	}
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
