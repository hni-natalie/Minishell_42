/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:45:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/24 14:27:37 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	DESC: Handles process status
	
	1. If process exited > update exit status
	2. If process terminated by signal > update exit status
	3. If SIGINT > print \n
	4. If SIGQUIT > print core dumped
*/
void	handle_process_status(int status, t_shell *shell)
{
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->last_exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", 2);	
			else if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
}

/*
	DESC: Handles error, prints explicit err msg and exit accordingly
	
	1. Check if cmd_path exist or not
	2. Check if it's absolute path or relative path
		- check access > error > permission > 126
		- else exit 127 > dir to cmd doesnt exist
	3. If neither > error > not cmd > 127
*/
void	handle_execute_error(char	*cmd_path, t_exec_node *exec_node)
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
