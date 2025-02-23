/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:53:43 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/18 14:41:46 by rraja-az         ###   ########.fr       */
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
		append = ft_strjoin(paths[i], "/");
		if (!append)
			return (NULL);
		fullpath = ft_strjoin(append, cmd);
		// free(append);
		if (access(fullpath, F_OK | X_OK) == 0)
			return (fullpath);
		// free(fullpath);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	*env_path;
	char	*cmd_path;
	char	**paths;

	cmd_path = is_relative_path(cmd);
	// printf("cmd path: %s\n", cmd_path); // debug
	if (cmd_path)
		return (cmd_path);
	env_path = extract_path("PATH", shell);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	//for (int i = 0; paths[i] ;i++) // debug
	//	printf("path[%i]= %s\n", i, paths[i]); // debug
	if (!paths)
		return (NULL);
	cmd_path = find_path(cmd, paths);
	// printf("cmd fullpath: %s\n", cmd_path); // debug
	// free_array(paths);
	return (cmd_path);
}
