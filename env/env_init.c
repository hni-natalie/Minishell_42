/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:48:34 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/21 08:25:49 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **env)
{
	char	**copied_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copied_env = malloc(sizeof(char *) * (i + 1));
	if (!copied_env)
		return (NULL);
	i = -1;
	while (env[++i])
		copied_env[i] = ft_strdup(env[i]);
	copied_env[i] = NULL;
	// free(env);
	return (copied_env);
}

char	*get_env_name(char *env)
{
	int		i;
	char	*name;
	
	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, env, i + 1);
	return (name);
}

char	*get_env_value(char *env)
{
	int	i;
	
	if (!env)
		return (NULL);
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
