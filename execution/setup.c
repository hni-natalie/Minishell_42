/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:16:26 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/23 10:00:36 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// setup_redir function and execute_node function will form a recursive
void	setup_redir(t_redir_node *redir_node, t_shell *shell)
{
	int	fd;
	int	pipefd[2];

	if (redir_node->file)
	{
		fd = open(redir_node->file, redir_node->mode, 0644);
		if (fd < 0)
		{
			perror(redir_node->file);
			exit(1);
		}
		dup2(fd, redir_node->fd);
	}
	else if (redir_node->heredoc)
	{
		pipe(pipefd);
		write(pipefd[1], redir_node->heredoc, ft_strlen(redir_node->heredoc));
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		free(redir_node->heredoc);
		redir_node->heredoc = NULL;
	}
	execute_node(redir_node->next, shell);
}

void	setup_pipe(t_pipe_node *pipe_node, t_shell *shell)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	pipe(pipefd);
	left_pid = fork();
	if (left_pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		setup_child(pipefd, pipe_node->left, shell);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		setup_child(pipefd, pipe_node->right, shell);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
}

void	setup_child(int *pipefd, t_node *node, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_node(node, shell);
	exit(shell->last_exit_status);
}
