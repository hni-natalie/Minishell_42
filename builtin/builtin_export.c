/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/11 13:29:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../include/minishell.h"

/*
	EXPORT
	DESC: Create / modify env and make them available to child process
	
	EG	: (1) export a NEW var > export VAR=value (make var/val part of env and shell)
		: (2) modify EXISTING var > export VAR=new_value (updates var with new value)
		: (3) LIST exported vars > export > prints all exported vars alphabetically
		
	FLOW : 
		1. Check args
			- no args > print list of exported vars ALPHABETICALLY (bubble sort)
			- has args > process each one
		2. Validate args
			- valid identifier (NAME=value format, start with letter/underscore)
			- reject invalid names
		3. Update / Add to env
			- if env exist > update its value
			- if it doesnt exist > add to array
		4. Mark the var as exported
			- make it available for child process
		5. Handle memory
			- malloc for new vars
*/

/* static int	env_len(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		i++;
	return (i);
} */

// using insertion sort
static void	sort_export_var(t_shell *shell)
{
	int	i;
	int	j;
	int len;
	char *tmp;

	if (!shell || !shell->env)
		return ;
	i = 1;
	len = 0;
	while (shell->env[len])
		len++;
	while (i < len)
	{
		tmp = shell->env[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(shell->env[j], tmp) > 0)
		{
			shell->env[j + 1] = shell->env[j];
			j--;
		}
		shell->env[j + 1] = tmp;
		i++;
	}
}

static void	print_export_var(char *var, t_shell *shell)
{
	int	i;
	
	if (!shell | !shell->env)
		return;
	sort_export_var(shell);
	i = 0;
	while (shell->env[i])
	{
		printf("declare -x %s\n", shell->env[i]);
		i++;
	}
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		print_export_var(shell->env[i], shell);
		shell->last_exit_status = 0;
		return (shell->last_exit_status);
	}
	while (args[i])
	{
		if (is_env_name(args[i], shell->env[i]))
			update_env(args[i], get_value(args[i]), false, shell);
		else
			update_env(args[i], get_value(args[i]), true, shell);
	}
	sort_export_var(shell);
	shell->last_exit_status = 0;
	return (shell->last_exit_status);
}
