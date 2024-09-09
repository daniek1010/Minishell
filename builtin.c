/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:36:34 by riporth           #+#    #+#             */
/*   Updated: 2024/09/09 21:57:49 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Iterate tru the command and then print
if echo without any args simply print \n*/
int	builtin_echo(t_command *cmd)
{
	int	i;
	int	e_status;

	if (cmd->args[0] && !cmd->args[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		i = 2;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		e_status = 0;
	}
	else
		e_status = echo_new_line(cmd);
	return (e_status);
}

/*Iterate tru the envp and then print out to the screen */
int	builtin_env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		ft_putendl_fd((*envp)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

/*Checks if key_value[] is passed, if yes then it proceed to use helper 
function(simply checks for the = identifier to split to key and value 
and then pass to set_env_var), if no key_value passed, simply search for
the '=' and then wrap value in a single quotes and print */
int	builtin_export(char ***envp, char *key_value[])
{
	int		i;
	int		e_status;
	char	*str;

	i = 0;
	if (key_value[1] == NULL)
	{
		while ((*envp)[i] != NULL)
		{
			str = ft_strchr((*envp)[i], '=');
			if (str)
			{
				*str = '\0';
				printf("declare -x %s=\"%s\"\n", (*envp)[i], str + 1);
				*str = '=';
			}
			i++;
		}
		return (0);
	}
	e_status = builtin_export_helper(key_value, envp);
	return (e_status);
}

/*Iterate tru the envp variables, searching for the Key, create new container
if key is found, rewrite the envp into new container, free envp and then pointer
to the new_envp*/
int	builtin_unset(char ***envp, char *key[])
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	while (key[k])
	{
		while ((*envp)[j])
			j++;
		while ((*envp)[i])
		{
			if (create_new(envp, key[k], i, j))
				break ;
			i++;
		}
		k++;
		i = 0;
		j = 0;
	}
	return (0);
}

/*Check for path with chdir , if path is empty, i use my getter to find HOME
and return the path to the HOME dir and use pwd to printout */
int	builtin_cd(char ***envp, const char *path)
{
	const char	*path_;
	char		*old_pwd;
	char		*new_path;

	path_ = builtin_cd_helper(envp, path);
	if (chdir(path_) != 0)
	{
		perror("CHDIR");
		return (2);
	}
	else
	{
		old_pwd = get_env_var((*envp), "PWD");
		set_env_var(envp, "OLDPWD", old_pwd);
		new_path = getcwd(NULL, 0);
		if (!new_path)
			return (3);
		set_env_var(envp, "PWD", new_path);
		free(new_path);
		return (0);
	}
}
