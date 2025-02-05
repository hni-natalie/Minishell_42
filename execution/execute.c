/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:49 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/05 11:15:30 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_ast(t_node *ast, t_shell *shell)
{ 
	pid_t	pid;
	
	// add check_builtin function in the if statement 
	if (!shell->pipe_in_prompt && ast->type == EXEC)
		execute_command(ast, shell);
	else
	{
		// handle signal there 
		pid = fork();
		if (pid == 0)
		{
			execute_node(ast, shell);
			exit(shell->last_exit_status);
		}	
	}
}

void	execute_node(t_node *node, t_shell *shell)
{
	t_exec_node		*exec_node;
	t_redir_node	*redir_node;
	t_pipe_node		*pipe_node;

	typecasting_node(node, &redir_node, &exec_node, &pipe_node);
	if (node->type == REDIR)
		setup_redir(redir_node, shell);
	else if (node->type == PIPE)
		setup_pipe(pipe_node, shell);
	else if (node->type == EXEC)
		execute_command(exec_node, shell);
}

void	execute_command(t_exec_node *exec_node, t_shell *shell)
{
	// link with builtin and execute command other than builtin 
	// by using execve
}

