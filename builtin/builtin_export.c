/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/10 17:28:02 by rraja-az         ###   ########.fr       */
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

static void	sort_export_var(char *var, t_shell *shell)
{
	
}

static void	print_export_var(char *var, t_shell *shell)
{
	
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
		print_export_var(shell->env[i], shell);
	while (args[i])
	{
		if (is_env_name(args[i], shell->env[i]))
			update_env(args[i], get_value(args[i]), false, shell);
		else
			update_env(args[i], get_value(args[i]), true, shell);
	}
}