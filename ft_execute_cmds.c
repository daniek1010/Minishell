/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 14:03:22 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_execute(t_command *command, char *envp[], t_infos *tokens)
{
	char	*path;
	
	if (tokens->red_index > 0)
		execute_command;
	path = ft_access(command->name, envp);
	if (path == NULL){
		errors("Couldn't find the executable");
		}
	if (execve(path, command->args, envp) == -1)
	{
		free(path);
		errors("Couldnt execute the cmd");
	}
}

char	*ft_access(char *av, char *envp[])
{
	char	**splitted;
	char	*path;
	int		i;

	splitted = ft_check_path(envp);
	i = -1;
	while (splitted[++i] != NULL)
	{
		path = join(splitted[i], av);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
	}
	if (splitted[i] == NULL)
	{
		ft_cleaner(splitted);
		return (NULL);
	}
	return (path);
}

char	*join(char *str, char *av)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, "     ");
	str = ft_strjoin(str, "/");
	path = ft_strjoin(str, cmd[0]);
	free(str);
	ft_cleaner(cmd);
	return (path);
}
