/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:46:20 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/08 17:27:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../include/minishell.h"

/*
	1. store_env(t_shell *shell)
	2. get_key(char *key)
	3. get_path(char *key)
	4. is_key(char *key, t_shell *shell)
	5. update_env (char *key, char *path, bool add, t_shell *shell)
	6. extend_env_array 
*/

/*
	ENV (with no options or no arguments)
	DESC: Prints all environment variables in newline

	FLOW:
		1. init env (done in init_shell)
			- store_env populate shell->env with env from envp
			- extract key and value via get_key and get_val
			- then calls update_env to add to the array
		2. manage env var
			- check, add, update, store env dynamically
		3. handle env cmd
			- iterates env list and prints those only with values
			- return exit status
	
	FUNCTIONS:
		1. store_env (t_shell *shell) > done in main->init shell
		2. get_key (char *key) > WHY? easier to just compare via name
			- extract name  > ft_strchr(env_var, '=') to find the =.
							> ft_substr(env_var, 0, index_of('=')) to extract the name
		3. get_path (char *key) > WHY? 
			- directly extracts path without going through KEY=PATH
			- used in store to populate (but we dont need this)
			- handle edge case without value
			- used when need to expand variable ($VAR) 
				- EG : run echo $SHELL
					 : /bin/bash

		4. is_key (char *key, t_shell *shell) 
			- (key exist) > WHY? check if var exist before modifying or adding it
			**prevent duplicate
			- EG: ["PATH=/usr/bin", "HOME=/home/user", "SHELL=/bin/bash", NULL]
				- run > export PATH=/new/path > REPLACE existing PATH
			**determine whether to add / update (export)
			- EG : if name exist > update its value | if name x exist > add new variable
				- export EDITOR=vim > if EDITOR exist, value gets updated to vim, else add EDITOR=vim to array
			**used with update env
			- EG : if true > update existing value, else add new "KEY=VALUE"
			** ensure proper unset behaviour
			- when removing env > check if exist before removing
			- if not found, unset does nothing

		5. update_key (char *key, char *path, bool add, t_shell *shell)
			- if key exist > update the path; find in array and replace it
				- free old path, replace with new path
			- if name doesnt exist > add new entry
				- reallocate shell->env[] to hold new var
				- append "KEY=PATH" to the array > set len to NULL
*/

char	*get_env_name(char *env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (ft_substr(env, 0, i));
		i++;
	}
	return(ft_strdup(env));
}

char	*get_env_value(char *env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (ft_substr(env, i + 1, ft_strlen(env) - i - 1));
		i++;
	}
	return (NULL);
}

void	get_env(t_shell *shell)
{
	int		i;
	char	**env;
	char	*env_name;
	char	*env_value;

	env = shell->env;
	if (env == NULL)
		return ;
	i = -1;
	while (env[++i])
	{
		env_name = get_env_name(env[i]);
		env_value = get_env_value(env[i]);
		update_env(env_name, env_value, true, shell);
		free(env_name);
		free(env_value);
	}
}

bool	is_env_name(char *name, t_shell *shell)
{
	int		i;
	char	*env_name;
	
	i = 0;
	while (shell->env[i])
	{
		env_name = get_env_name(shell->env[i]);
		if (ft_strncmp(name, env_name, ft_strlen(name)) == 0)
		{
			free(env_name);
			return (true);
		}
		free(env_name);
		i++;
	}
	return (false);
}

void	update_env(char *name, char *value, bool add, t_shell *shell)
{
	int		i;
	char	*env_name;
	char	*new_value;

	i = 0;
	while (shell->env[i])
	{
		env_name = get_env_name(shell->env[i]);
		if (ft_strncmp(name, env_name, ft_strlen(env_name) + 1) == 0)
		{
			free(env_name);
			free(shell->env[i]);
			new_value = ft_strjoin_three(name, '=', value);
			shell->env[i] = new_value;
			return ;
		}
		free(env_name);
		i++;
	}
	if (add == true)
		shell->env = extend_env_array(shell->env, name, value);
}

char	**extend_env_array(char **env, char *name, char *value)
{
	int		i;
	int		len;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strjoin_three(name, '=', value);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}
