/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/23 12:34:59 by rraja-az         ###   ########.fr       */
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
			- no args > print list of exported vars ALPHABETICALLY (insertion sort)
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

// using insertion sort
static void sort_export_env(char **export_env)
{
    int i;
    int j;
    char *tmp;

    if (!export_env || !export_env[0])
        return;
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

static void print_export_env(t_shell *shell)
{
    int		i;
	char	*equal;

	
    if (!shell->export_env)
        return;
    i = 0;
    while (shell->export_env[i])
    {
		equal = ft_strchr(shell->export_env[i], '=');
        if (equal)
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", shell->export_env[i], equal + 1);
			*equal = '=';
		}
		else 
			printf("declare -x %s\n", shell->export_env[i]);
		i++;
	}
	//free_array(shell->export_env);
}

/* 
	DESC: Extract variable name
	
	1. Extract name
	2. Check if name is valid
		- error > prints error > returns failure > updates exit status
	3. Extract value 
	4. Check if it var exist in shell > update value
	5. 
	
*/
static	int	handle_equal(char *equal, char *argv, t_shell *shell)
{
	int		len;
	char	name[PATH_MAX];
	char	*value;

	len = equal - argv;
	ft_strlcpy(name, argv, len + 1);
	if (!is_valid_env_name(name))
	{
		printf("minishell: export: %s: not a valid identifier\n", name);
        shell->last_exit_status = FAILURE;
        return (shell->last_exit_status);
	}
	value = equal + 1;
	shell->env = extend_env_array(shell->env, name, value);
    shell->export_env = extend_env_array(shell->export_env, name, value);
	sort_export_env(shell->export_env);
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}

int builtin_export(char **argv, t_shell *shell)
{
    int		i;
	char	*equal;

    if (!argv[1])
    {
        print_export_env(shell);
        shell->last_exit_status = SUCCESS;
        return (shell->last_exit_status);
    }
    i = 0;
    while (argv[++i])
    {
		equal = ft_strchr(argv[i], '=');
		if (equal && handle_equal(equal, argv[i], shell))
			return (shell->last_exit_status);
		else if (!equal)
		{
			if (!is_valid_env_name(argv[i]))
			{
				printf("minishell: export: %s: not a valid identifier\n", argv[i]);
				shell->last_exit_status = FAILURE;
			}
			else if (!is_env_name(argv[i], shell))
			{
				shell->export_env = extend_env_array(shell->export_env, argv[i], NULL);
				sort_export_env(shell->export_env);
			}
		}
    }
    return (shell->last_exit_status);
}
