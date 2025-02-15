/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:53:43 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/15 16:31:29 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	ABSOLUTE PATH : Full path from root dir(/), always starts with /
	/usr/bin/ls	
	/home/user/documents/file.txt

	RELATIVE PATH : Relative to current directory, does not start with /
	documents/file.txt
	../file.txt
*/



char	*get_path(char *cmd, t_shell *shell)
{
	char	*env_path;
	char	*cmd_path;
	char	**paths;

	
	
	// find THE path variable
		// loop through all vars and stops at PATH
		// skip PATH=; env_path now holds value only (after equal sign)
	
	// split path into directories
		// use ft_split to split into array of directories
		
	// try each directory
		// loop each directory in path
		// construct full path for the SPECIFIC command
		// call access to check if file exist and executable
		// if not > it frees the full path and try and
}