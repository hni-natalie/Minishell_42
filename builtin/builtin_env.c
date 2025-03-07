/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:22:08 by rraja-az          #+#    #+#             */
/*   Updated: 2025/03/07 23:36:45 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	ENV (with no options or arguments)
	DESC: Prints all environment variables in newline
*/

int	builtin_env(char **args, t_shell *shell)
{
	int		i;
	char	*path;

	if (args[1])
	{
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
	path = get_directory("PATH", shell);
	if (!path || !path[0])
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		shell->last_exit_status = 127;
		return (shell->last_exit_status);
	}
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
