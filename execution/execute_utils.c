/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:45:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/25 12:55:39 by rraja-az         ###   ########.fr       */
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
static void	print_execute_error(char *argv, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_execute_error(char	*cmd_path, t_exec_node *exec_node)
{
	if (cmd_path)
		free(cmd_path);
	if (exec_node->argv[0][0] == '/' || (exec_node->argv[0][0] == '.'
			&& exec_node->argv[0][1] == '/'))
	{
		if (access(exec_node->argv[0], F_OK) == 0)
		{
			print_execute_error(exec_node->argv[0], "Permission denied");
			exit(126);
		}
		print_execute_error(exec_node->argv[0], "No such file or directory");
		exit(127);
	}
	print_execute_error(exec_node->argv[0], "command not found");
	if (errno == EACCES)
		exit (126);
	exit(127);
}
