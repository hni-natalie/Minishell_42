/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:22:08 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/14 16:47:49 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	ENV (with no options or no arguments)
	DESC: Prints all environment variables in newline
*/
int	builtin_env(char **args, t_shell *shell)
{
	int	i;

	if (args[1] == NULL)
	{
		i = 0;
		while (shell->env[i])
		{
			printf("%s\n", shell->env[i]);
			i++;
		}
	}
	shell->last_exit_status = 0;
	return (shell->last_exit_status);
}