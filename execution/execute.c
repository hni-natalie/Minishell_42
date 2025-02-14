/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:49 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/14 11:12:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	DESC: Parses AST, determines execution type 
		: Execute command or pipeline whilst ensuring proper signal handling
		> by handling diff exex cases wether there is a pipeline / builtin
	
	1. Check if current cmd is a simple command (EXEC) and not in a pipeline
		- if command is builtin > exec without forking a child process
		- builtins dont fork because they affect the shell's state

*/
void	parse_ast(t_node *ast, t_shell *shell)
{ 
	if (!shell->pipe_in_prompt && ast->type == EXEC)
		execute_parent(ast, shell);
	else
		execute_child(ast, shell);
}

void	execute_parent(t_node *ast, t_shell *shell)
{
	t_exec_node	*exec_node;
	
	exec_node = (t_exec_node *)ast;
	if (exec_node->argv[0] && is_builtin(exec_node->argv[0]))
		shell->last_exit_status = exec_builtin(exec_node->argv, shell);
	else
		execute_command(ast, shell);
}

/* 
	DESC: Handles pipe and redir

	1. IGNORE signals in parent BEFORE forking so only child reacts to signal
		- WHY NEED to ignore first? 
			> if parent receives ctrl+c, child might not even exec
	2. FORK
		- restore default signal handlers to child
		- child exec cmd > exit
	3. WAIT for child to finish
		restore parent's signal after child finishes
	3. EXIT STATUS
		- capture child exits so $? (similar to Bash)
*/
void	execute_child(t_node *ast, t_shell *shell)
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
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
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
	if (execve(exec_node->argv[0], exec_node->argv, shell->env) == -1)
	{
		printf("minishell: %s: command not found\n", exec_node->argv[0]);
		shell->last_exit_status = 127;
		exit(127);
	}
}
