/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:24:44 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/20 21:16:36 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum node_type
{
	EXEC,
	REDIR,
	PIPE,
}	t_node_type;

/*
	INPUT 	<
	OUTPUT 	>
	APPEND 	>>
	HEREDOC <<
*/
typedef enum redir_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_redir_type;

/* 
	General structure for each of the nodes in the AST
*/
typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_pipe_node
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe_node;

typedef struct s_exec_node
{
	int		type;
	char	**argv;
}	t_exec_node;

typedef struct s_redir_node
{
	int		type;
	int		mode;
	int		fd;
	char	*file;
	char	*heredoc;
	t_node	*next;	
}	t_redir_node;

typedef struct s_shell
{
	char	**env;
	int		last_exit_status;
	int		pipe_in_prompt;
}	t_shell;

#endif