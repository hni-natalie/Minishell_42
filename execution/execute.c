/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:49 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/19 14:38:20 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	DESC: Parses execution, determines execution type 
		: Execute command or forks (ensuring proper signal handling)
	
	1. Check if ast is an EXEC node
	2. Check if cmd is a builtin > true > exc_builtin
		- builtin is executed directly in parent process
			because the modify the shell state
	3. Else (if not builtin) > fork
*/

void	parse_ast(t_node *ast, t_shell *shell)
{
	t_exec_node	*exec_node;

	if (!ast)
		return;
	if (ast->type == EXEC)
	{
		exec_node = (t_exec_node *)ast;
		if (exec_node->argv[0] && is_builtin(exec_node->argv[0]))
		{
			shell->last_exit_status = exec_builtin(exec_node->argv, shell);
			return;
		}
	}
	execute_fork(ast, shell);
}

/* 
	DESC: Creates child process, execute the cmd

	1. Supress signals from parent before forking
		- WHY? if we ctrl+c in parent, child wont execute
	2. Fork (child) > restore signals > execute cmd
	3. Parent waits for child to end > restore parent's signals
	4. Handle child process exit status
		- exit status = 128 + 2(SIGINT) / 3(SIGQUIT) 
*/
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
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit_status = 128 + WTERMSIG(status);
	}
}

/*
	DESC: Handles execution of AST nodes
	USE	: parse_ast calls nodes(pipe/redir) that needs forking
*/
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
	DESC: Runs actual cmd (builtin / execve) if node is simple cmd
	Check if ;
	1. argv is empty string > print as bash > return
	2. argv is_built in > exec_built_in
	3. agrv cmd not found > return 127 > exit child process
	127 : exit code for "command not found"

	WHY empty only return and invalid exits?
	- empty doesnt even execute = parent process
	- invalid forks child to exec, child fails to find cmd and prints error
		- since execve fails > child must exit
	WHY is there another call for exec_builtin here? 
	- if builtin is inside pipe/redir, then it is exec in child
*/
void	execute_command(t_exec_node *exec_node, t_shell *shell)
{
	char	*cmd_path;
	
	if (!exec_node->argv[0])
		return;
	if (is_builtin(exec_node->argv[0]))
	{
		shell->last_exit_status = exec_builtin(exec_node->argv, shell);
		return ;
	}
	cmd_path = get_path(exec_node->argv[0], shell);
	if (!cmd_path || execve(cmd_path, exec_node->argv, shell->env) == -1)
		execute_error(cmd_path, exec_node);
}
