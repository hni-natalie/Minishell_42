/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:16:01 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/19 11:13:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return ((ft_strcmp(cmd, "echo") == 0)
		|| (ft_strcmp(cmd, "/usr/bin/echo") == 0)
		|| (ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "pwd") == 0)
		|| (ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "unset") == 0)
		|| (ft_strcmp(cmd, "env") == 0)
		|| (ft_strcmp(cmd, "exit") == 0));
}

/* 
	DESC: Runs the builtin command
	RETURNS : last exit status from builtins
	** previously return void and just execute the builtin
	** return int because this fx is a dispacther,
		otherwise it will lose the exit status from builtin
*/
int		exec_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (FAILURE);
	else if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/usr/bin/echo") == 0)
		return (builtin_echo(cmd, shell));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(cmd, shell));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, shell));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd, shell));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd, shell));
	return (FAILURE);
}

/*
int		exec_builtin(char **cmd, t_shell *shell)
{
	int				i;
	static const	t_builtin builtins[] = {{"echo", builtin_echo},
		{"cd", builtin_cd}, {"pwd", builtin_pwd}, {"export", builtin_export},
		{"unset", builtin_unset}, {"env", builtin_env}, {"exit", builtin_exit},
		{NULL, NULL}};

	if (!cmd || cmd[0])
		return (1);
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(cmd[0], builtins[i].name) == 0)
			return (builtins[i].func(cmd, shell));
		i++;
	}
	return (1);
}
*/
