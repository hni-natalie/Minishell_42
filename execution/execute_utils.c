/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:45:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/27 11:35:54 by hni-xuan         ###   ########.fr       */
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

void	shift_argv(t_exec_node *exec_node)
{
	int	i;

	if (!exec_node || !exec_node->argv)
		return;

	// printf("Before shifting:\n");
	// for (i = 0; exec_node->argv; i++)
	// 	printf("argv: %s\n", exec_node->argv[i]); // debug
	while (exec_node->argv[0] && (ft_strcmp(exec_node->argv[0], "") == 0)) // shift only if argv[0] is NULL
	{
		i = 0;
		while (exec_node->argv[i]) // shift everything left
		{
			exec_node->argv[i] = exec_node->argv[i + 1];
			i++;
		}
		exec_node->argv[i] = NULL;
	}
	// printf("After shifting:\n");
	// for (i = 0; exec_node->argv; i++)
	// 	printf("argv: %s\n", exec_node->argv[i]); // debug
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

void	handle_execute_error(char *cmd_path, t_exec_node *exec_node)
{
	bool	is_path;

	is_path = (exec_node->argv[0][0] == '/' ||
        (exec_node->argv[0][0] == '.' && (exec_node->argv[0][1] == '/' ||  
        (exec_node->argv[0][1] == '.' && exec_node->argv[0][2] == '/'))));
	if (!cmd_path && !is_path)
	{
		print_execute_error(exec_node->argv[0], "command not found");
		exit(127);
	}
	else if (errno == EACCES)
	{
		print_execute_error(exec_node->argv[0], "Permission denied");
		exit(126);
	}
	else if (errno == ENOTDIR)
	{
		print_execute_error(exec_node->argv[0], "No such file or directory");
		exit(126);
	}
	print_execute_error(exec_node->argv[0], "No such file or directory");
	if (is_path && access(exec_node->argv[0], F_OK) == -1)
		exit (127);
	exit(126);
	// if (cmd_path)
	// 	free(cmd_path);
}
