/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:53:43 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/17 13:44:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	WHY : To determine how to find cmd in filesystem
	ABSOLUTE PATH : Starts with / (EG: /usr/bin/ls)
	RELATIVE PATH : Does not start with / (EG : my_program or ./my_program)
*/
static char	*is_relative_path(char *cmd)
{
	if ((cmd[0] == '.' && cmd[1] == '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (NULL);
}

static char	*extract_path(char *path, t_shell *shell)
{
	int	i;
	int	len;
	
	if (!shell->env)
		return (NULL);
	i = 0;
	len = ft_strlen(path);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], path, len) == 0 && shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*append;
	char	*fullpath;
	

	if (!cmd || !paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		append = ft_strjoin("/", cmd);
		fullpath = ft_strjoin(paths[i], append);
		free(append);
		if (access(fullpath, F_OK | X_OK) == 0)
			return (fullpath);
		free(fullpath);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	*env_path;
	char	*cmd_path;
	char	**paths;

	// check if the cmd is an absolute or relative path
	cmd_path = is_relative_path(cmd);
	if (cmd_path)
		return (cmd_path);
	// find THE path variable
		// loop through all vars and stops at PATH
		// skip PATH=; env_path now holds value only (after equal sign)
	env_path = extract_path("PATH", shell);
	if (!env_path)
		return (NULL);
	// split path into directories
		// use ft_split to split into array of directories
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	cmd_path = find_path(cmd, paths);
	free_array(paths);
	return (cmd_path);
}
