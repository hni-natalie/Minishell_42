/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:05:28 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/23 14:17:22 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define RESET "\033[0m"

# define SUCCESS 0
# define FAILURE 1
# define ERROR 2
# define QUOTE_ERROR "minishell: syntax error: unclosed quote"
# define PIPE_ERROR "minishell: syntax error near unexpected token '|'"
# define NEWLINE_ERROR "minishell: syntax error near unexpected token 'newline'"
# define REDIR_ERROR "minishell: syntax error near unexpected token '<' '>'"
# define SEMICOLON_ERROR "minishell: syntax error near unexpected token ';'"
# define HEREDOC_ERROR "minishell: warning: here-document delimited by end-of-file (wanted '"

# define OPEN_QUOTE 1
# define CLOSE_QUOTE 0

# define YES 1
# define NO 0

extern int	g_signal;

// main.c
void	init_shell(t_shell *shell, char **env);
void	start_shell(t_shell *shell);

// check.c
int		empty_line(char *prompt);
void	free_arr(char **arr);
int		syntax_error(char *prompt);
int		quote_opening(char *prompt);
void	print_error(char *error, char *prompt);

// signal.c
void	sigint_handler(int signum);
void	handle_sigint(t_shell *shell);

// token.c
int		grab_token(char *prompt, int *idx, char *word_in_tok);
void	label_token(char *prompt, int *token, int *idx);
void	word_token(char *prompt, int *token, int *idx);

// parsing.c
t_node	*parse_node(char *prompt, t_shell *shell);
t_node	*parse_exec(char *prompt, int *i, t_shell *shell);
void	malloc_argv(char *prompt, t_exec_node *exec_node);
t_node	*parse_redir(t_node *node, char *prompt, int *i, t_shell *shell);
t_node	*redir_node(char *arg, int redir_type, t_node *node, t_shell *shell);

// arg_handler.c
void	handle_arg(char **argv, t_shell *shell);
char	*check_arg(char *arg, t_shell *shell);
void	check_quote(int *quote, char *c, int *i, int action);
char	*update_arg(char *arg, int *i, char *new_arg, t_shell *shell);
char	*join_arg(char *new_arg, char *arg, int *i, int quote);

// heredoc
char	*handle_heredoc(char *arg, t_shell *shell);
char	*check_delimeter(char *delimeter, int *quoted_delimeter);
void	heredoc_input(int *fd, char *delimeter);
void	read_heredoc_input(int *fd, char **input);

// heredoc_utils
char	*update_input(char *input, t_shell *shell);
char	*join_input(char *new_input, char *input, int *i);
void	handle_heredoc_signal(int status, t_shell *shell);
void	handle_child_signal(int signum);

// free.c
void	free_ast(t_node *node);
void	free_redir_data(t_redir_node *r_node);
void	typecasting_node(t_node *node, t_redir_node **r_node,
			t_exec_node **e_node, t_pipe_node **p_node);

// init.c
t_node	*init_exec_node(void);
t_node	*pipe_node(t_node *left_node, t_node *right_node);
void	init_redir_node(t_redir_node *redir_node, int redir_type);
void	insert_node(t_node *node, t_redir_node *redir_node);

// utils.c
char	*get_env(char **env, char *input);

#endif