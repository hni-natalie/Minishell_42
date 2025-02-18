/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:45:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/17 16:46:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	DESC: Handles error, prints explicit err msg and exit accordingly
	
	1. Check if cmd_path exist or not
	2. Check if it's absolute path or relative path
		- check access > error > permission > 126
		- else exit 127 > dir to cmd doesnt exist
	3. If neither > error > not cmd > 127
*/
void	execute_error(char	*cmd_path, t_exec_node *exec_node)
{
	if (cmd_path)
		free(cmd_path);
	if (exec_node->argv[0][0] == '/' || (exec_node->argv[0][0] == '.' && exec_node->argv[0][1] == '/'))
	{
		if (access(exec_node->argv[0], F_OK) == 0)
		{
			printf("minishell: %s: Permission denied\n", exec_node->argv[0]);
			exit(126);
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", exec_node->argv[0]);
			exit(127);
		}
	}
	else
	{
		printf("minishell: %s: command not found\n", exec_node->argv[0]);
		exit(127);
	}
}
