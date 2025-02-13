/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:49 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/13 09:23:06 by rraja-az         ###   ########.fr       */
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

/* 
	Check if ;
	1. argv is empty string > print as bash > return
	2. argv is_built in > exec_built_in
	3. agrv cmd not found > return 127 > exit child process
	127 : exit code for "command not found"

	WHY empty only return and invalid exits?
	- empty doesnt even execute = parent process
	- invalid forks child to exec, child fails to find cmd and prints error
		- since execve fails > child must exit
*/
void	execute_command(t_exec_node *exec_node, t_shell *shell)
{
	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
	{
		printf("minishell: command not found\n");
		shell->last_exit_status = 127;
		return ;
	}
	if (is_builtin(exec_node->argv[0]))
	{
		shell->last_exit_status = exec_builtin(exec_node->argv, shell);
		return ;
	}
	if (!execve(exec_node->argv[0], exec_node->argv, shell->env))
	{
		printf("minishell: %s: command not found\n", exec_node->argv[0]);
		shell->last_exit_status = 127;
		exit(127);
	}
}

