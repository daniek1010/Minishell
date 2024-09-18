/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:06:40 by riporth           #+#    #+#             */
/*   Updated: 2024/09/18 14:13:07 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var_up_2(char *str, t_infos *tokens)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (is_valid_var_char(str[i + 1]) || str[i + 1] == '?')
				str = add_var(str, &i, tokens);
			else
				i++;
		}
		else
			i++;
	}
	return (str);
}

char	*ft_token_fill_2(const char *str, char *list)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	list = (char *)malloc(sizeof(char) * (i + 1));
	list[i] = '\0';
	i = 0;
	while (str[i + 1] != '\0')
	{
		list[i] = str[i];
		i++;
	}
	return (list);
}

char	**ft_token_spliter_2(char const *s, t_infos *tokens)
{
	char	**list;

	list = (char **)malloc(sizeof(char *) * (2));
	if (!list)
		return (NULL);
	list[1] = NULL;
	list[0] = ft_token_fill_2(s, list[0]);
	list[0] = ft_var_up_2(list[0], tokens);
	return (list);
}
