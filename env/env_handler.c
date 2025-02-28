/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:48:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/28 08:55:18 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*set_new_env(char *s1, char c, char *s2)
{
	int		len;
	char	*tmp;
	char	*new_env;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	tmp = malloc((len + 2) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s1, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	new_env = ft_strjoin(tmp, s2);
	if (!new_env)
		return (NULL);
	free(tmp);
	return (new_env);
}

static bool	check_and_update_env(char **env, char *name, char *value)
{
	int		i;
	char	*env_name;
	char	*new_value;

	i = 0;
	while (env[i])
	{
		env_name = get_env_name(env[i]);
		if (ft_strncmp(name, env_name, ft_strlen(name) + 1) == 0)
		{
			free(env_name);
			free(env[i]);
			new_value = set_new_env(name, '=', value);
			env[i] = new_value;
			return (true);
		}
		free(env_name);
		i++;
	}
	return (false);
}

void	update_env(char *name, char *value, bool add, t_shell *shell)
{
	bool	found_env;
	bool	found_export;

	found_env = check_and_update_env(shell->env, name, value);
	found_export = check_and_update_env(shell->export_env, name, value);
	if (add)
	{
		if (!found_env)
			shell->env = extend_env_array(shell->env, name, value);
		if (!found_export)
			shell->export_env = extend_env_array(shell->export_env, name,
					value);
	}
}

static char	**new_env_arr(char **env, char *name, char *value)
{
	int		i;
	int		len;
	char	**new_env_arr;

	len = 0;
	while (env[len])
		len++;
	new_env_arr = ft_calloc((len + 2), sizeof(char *));
	if (!new_env_arr)
		return (free_array(env), NULL);
	i = -1;
	while (++i < len)
	{
		new_env_arr[i] = ft_strdup(env[i]);
		if (!new_env_arr[i])
			return (free_array(new_env_arr), NULL);
	}
	if (value)
		new_env_arr[i] = set_new_env(name, '=', value);
	else
		new_env_arr[i] = ft_strdup(name);
	if (!new_env_arr[i])
		return (free_array(new_env_arr), NULL);
	new_env_arr[i + 1] = NULL;
	return (free_array(env), new_env_arr);
}

char	**extend_env_array(char **env, char *name, char *value)
{
	int		i;
	char	*env_name;

	if (!value)
	{
		i = 0;
		while (env[i])
		{
			env_name = get_env_name(env[i]);
			if (ft_strncmp(name, env_name, ft_strlen(name) + 1) == 0)
			{
				free(env_name);
				return (env);
			}
			free(env_name);
			i++;
		}
	}
	return (new_env_arr(env, name, value));
}
