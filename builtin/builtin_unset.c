/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/28 08:13:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	UNSET (with no options)
	DESC: Remove var from (shell/export) env
*/

static bool	is_env_var(char *var, char **env)
{
	int		i;
	char	*env_name;
	bool	found;

	i = 0;
	found = false;
	while (env[i])
	{
		env_name = get_env_name(env[i]);
		if (ft_strncmp(var, env_name, ft_strlen(var) + 1) == 0)
			found = true;
		free(env_name);
		i++;
	}
	return (found);
}

static void	remove_env_var(char *var, char **env)
{
	int		i;
	char	*env_name;

	i = 0;
	while (env[i])
	{
		env_name = get_env_name(env[i]);
		if (ft_strncmp(var, env_name, ft_strlen(var) + 1) == 0)
		{
			free(env_name);
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			return ;
		}
		free(env_name);
		i++;
	}
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	if (!argv[i])
	{
		shell->last_exit_status = SUCCESS;
		return (shell->last_exit_status);
	}
	while (argv[i])
	{
		if (is_env_var(argv[i], shell->env))
			remove_env_var(argv[i], shell->env);
		if (is_env_var(argv[i], shell->export_env))
			remove_env_var(argv[i], shell->export_env);
		i++;
	}
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
