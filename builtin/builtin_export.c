/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/23 19:05:15 by rraja-az         ###   ########.fr       */
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

static void print_export_error(char *argv)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static void handle_without_equal(char *argv, t_shell *shell)
{
	if (!argv[0] || !is_valid_env_name(argv))
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	if (!is_env_name(argv, shell->env))
	
	
		shell->export_env = extend_env_array(shell->export_env, argv, NULL);
		sort_export_env(shell->export_env);
}

static void handle_with_equal(char *equal, char *argv, t_shell *shell)
{
	char	name[PATH_MAX];
	char	*value;

	if (equal == argv)
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	ft_strlcpy(name, argv, equal - argv + 1);
	if (!name[0] ||!is_valid_env_name(name))
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	value = equal + 1;
	update_env(name, value, true, shell);
	sort_export_env(shell->export_env);
	shell->last_exit_status = SUCCESS;
}

int builtin_export(char **argv, t_shell *shell)
{
    int     i;
    char    *equal;

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
        if (equal)
			handle_with_equal(equal, argv[i], shell);
		else
			handle_without_equal(argv[i], shell);
    }
    return (shell->last_exit_status);
}  
