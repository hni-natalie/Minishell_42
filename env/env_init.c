/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:48:34 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/15 14:48:37 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//return (NULL);
	return (ft_strdup(""));
}

// buffer store; env for builtins
void	get_env_var(t_shell *shell)
{
	int		i;
	char	**env;
	char	*env_name;
	char	*env_value;

	env = shell->env;
	if (env == NULL)
		return ;
	i = 0;
	while (env[i])
	{
		env_name = get_env_name(env[i]);
		env_value = get_env_value(env[i]);
		update_env(env_name, env_value, true, shell);
		free(env_name);
		free(env_value);
		i++;
	}
}
