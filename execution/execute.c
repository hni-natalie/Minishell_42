/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:49 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/03/07 23:38:38 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_ast(t_node *ast, t_shell *shell)
{
	t_exec_node	*exec_node;

	if (!ast)
		return ;
	if (ast->type == EXEC)
	{
		exec_node = (t_exec_node *)ast;
		if (exec_node->argv[0] && is_builtin(exec_node->argv[0]))
		{
			shell->last_exit_status = exec_builtin(exec_node->argv, shell);
			return ;
		}
	}
	execute_fork(ast, shell);
}

void	execute_fork(t_node *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_node(ast, shell);
		exit(shell->last_exit_status);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	handle_process_status(status, shell);
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
	char	*cmd_path;

	if (shell->argv_with_expansion)
		shift_argv(exec_node);
	cmd_path = NULL;
	cmd_path = get_path(exec_node->argv[0], shell);
	if (!cmd_path || execve(cmd_path, exec_node->argv, shell->env) == -1)
		handle_execute_error(cmd_path, exec_node);
}
