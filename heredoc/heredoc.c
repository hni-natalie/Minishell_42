/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:49:45 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/27 16:18:32 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Note:
quoted delimeter and unquoted delimeter behave differently
	quoted delimeter expand the variable & substitute the command
	unquoted delimeter won't expand the variable & substitute the command

Signal handling is needed in heredoc to handle interruptions eg. Ctrl+C
	
*/
char	*handle_heredoc(char *delimeter, t_shell *shell)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	int		quoted_delimeter;
	char	*input;

	input = ft_strdup("");
	quoted_delimeter = NO;
	delimeter = check_delimeter(delimeter, &quoted_delimeter);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_input(fd, delimeter);
	if (pid > 0)
	{
		read_heredoc_input(fd, &input);
		waitpid(pid, &status, 0);
		handle_heredoc_signal(status, shell);
	}
	if (quoted_delimeter == NO)
		input = update_input(input, shell);
	else
		free(delimeter);
	return (input);
}

void	read_heredoc_input(int *fd, char **input)
{
	int		buffer_read;
	char	buffer[1024];
	int		total_read;
	char	*temp;

	close(fd[1]);
	signal(SIGINT, handle_child_signal);
	total_read = 0;
	buffer_read = read(fd[0], buffer, sizeof(buffer));
	while (buffer_read > 0)
	{
		temp = malloc(total_read + buffer_read + 1);
		if (*input)
		{
			ft_memcpy(temp, *input, total_read);
			free(*input);
		}
		ft_memcpy(temp + total_read, buffer, buffer_read);
		total_read += buffer_read;
		temp[total_read] = 0;
		*input = temp;
		buffer_read = read(fd[0], buffer, sizeof(buffer));
	}
	close(fd[0]);
}

void	heredoc_input(int *fd, char *delimeter)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd(HEREDOC_ERROR, 2);
			ft_putstr_fd(delimeter, 2);
			ft_putendl_fd("')", 2);
			break ;
		}
		if (!ft_strcmp(line, delimeter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	exit(SUCCESS);
}
