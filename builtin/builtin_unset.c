/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/14 16:48:00 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	DESC: Remove env / shell vars
		: If var was exported, it no longer be available to child process
	  EG: run unset MY_VAR, MY_VAR is removed from env
		: if MY_VAR was exported, it no longer is available to any subprocess
			spawned after unset
	
	FLOW:
		1. Check for no args > print error > return error 
		2. Check args > check for invalid > print error 
			> else > var valid > remove var
		3. return status
*/

static bool	is_env_var(char *var, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		j = 0;
		while (var[j] && shell->env[i][j] && shell->env[i][j] != '=')
		{
			if (var[j] != shell->env[i][j])
				break ;
			j++;
		}
		if (var[j] == '\0' && shell->env[i][j] == '=')
			return (true);
		i++;
	}
	return (false);
}

static void	remove_env_var(char *var, t_shell *shell)
{
	int	i;
	
	i = 0;
	// find index of var
	while (shell->env[i])
	{
		if ((ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0) && (shell->env[i][ft_strlen(var)] == '='))
			break;
		i++;
	}
	// if var not found
	if (!shell->env[i])
		return;
	// free(shell->env[i]); // is it malloced?
	// shift elements left
	while (shell->env[i + 1])
	{
		shell->env[i] = shell->env[i + 1];
		i++;
	}
	shell->env[i] = NULL; 
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	if (!argv[i])
	{
		printf("unset: not enough arguments\n");
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
	while (argv[i])
	{
		if (!is_env_var(argv[i], shell))
			printf("unset: variable does not exist\n");
		else
			remove_env_var(argv[i], shell);
		i++;
	}
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
