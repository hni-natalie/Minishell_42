/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/23 08:54:38 by rraja-az         ###   ########.fr       */
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

/* static bool	is_env_var(char *var, t_shell *shell)
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
} */

static bool is_env_var(char *var, char **env)
{
    int     i;
    char    *env_name;
    bool    found;

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

static void remove_env_var(char *var, char **env)
{
    int i;
    char *env_name;
    
    i = 0;
    while (env[i])
    {
        env_name = get_env_name(env[i]);
        if (ft_strncmp(var, env_name, ft_strlen(var) + 1) == 0)
        {
            free(env_name);
            free(env[i]);
            // shift elements left
            while (env[i + 1])
            {
                env[i] = env[i + 1];
                i++;
            }
            env[i] = NULL;
            return;
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
		printf("unset: not enough arguments\n");
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
	while (argv[i])
	{
		if (!is_env_var(argv[i], shell->env) && !is_env_var(argv[i], shell->export_env))
			printf("unset: variable does not exist\n");
		else
			remove_env_var(argv[i], shell->env);
			remove_env_var(argv[i], shell->export_env);
		i++;
	}
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
