/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/21 15:14:00 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// print error?


/*
	DESC: Verifies a valid new env var
		: follows syntax rules
		: NAME must start with alpha, can only contain alphanum
*/
static bool	is_valid_env_name(const char *name)
{
	int	i;
	
	if (!name || !name[0] || ((!isalpha(name[0])) && name[0] != '_'))
		return (false);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// copy the env var because we dont want to modify the original env
static char	**export_var_copy(t_shell *shell, int *len)
{
	int		i;
	char	**export_env;
	
	*len = 0;
	while (shell->env[*len])
		(*len)++;
	export_env = malloc((*len + 1) * sizeof(char *));
	if (!export_env)
		return (NULL);
	i = 0;
	while(i < *len)
	{
		export_env[i] = ft_strdup(shell->env[i]);
		if (!export_env[i])
		{
			free_array(export_env);
			return (NULL);
		}
		i++;
	}
	export_env[*len] = NULL;
	return (export_env);
}

// using insertion sort
static void	sort_export_var(char **export_env)
{
	int	i;
	int	j;
	char *tmp;

	if (!export_env || !export_env[0])
		return ;
	i = 1;
	while (export_env[i])
	{
		tmp = export_env[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(export_env[j], tmp) > 0)
		{
			export_env[j + 1] = export_env[j];
			j--;
		}
		export_env[j + 1] = tmp;
		i++;
	}
}

static void	print_export_var(char **export_env, int len)
{
	int	i;
	
	if (!export_env || !export_env[0])
		return;
	sort_export_var(export_env, len);
	i = 0;
	while (export_env[i])
	{
		printf("declare -x \"%s\"\n", export_env[i]);
		i++;
	}
}

int	builtin_export(char **argv, char **export_env, t_shell *shell)
{
	int		i;
	char	**export_env;

	export_env = export_var_copy(shell, &len);
	if (!argv[1])
	{
		print_export_var(export_env, len);
		shell->last_exit_status = SUCCESS;
		return (shell->last_exit_status);
	}
	i = 0;
	while (argv[++i])
	{
		if (!is_valid_env_name(argv[i]))
		{
			printf("minishell: export: %s: not a valid identifier\n", argv[i]);
			shell->last_exit_status = FAILURE;
			return (shell->last_exit_status);
		}	
		if (is_env_name(argv[i], shell))
			update_env(argv[i], get_env_value(argv[i]), false, shell);
		else
			update_env(argv[i], get_env_value(argv[i]), true, shell);
	}
	sort_export_var(shell);
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
