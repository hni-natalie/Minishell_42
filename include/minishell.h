/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:05:28 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/22 11:17:56 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
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

# define PATH_MAX 4096
// max buffer size for file paths (CLI: getconf PATH_MAX /)
// LINUX : 4096 | MAC : 1024

extern int	g_signal;

// main.c
void	init_shell(t_shell *shell, char **env);
void	start_shell(t_shell *shell);
//void	free_arr(char **arr);
void	print_error(char *error, char *prompt);

// signal.c
void	sigint_handler(int signum);
void	handle_sigint(t_shell *shell);
void	handle_child_signal(int signum);
void	handle_child_exit(int left_status, int right_status, t_shell *shell);

// check.c
int		empty_line(char *prompt);
int		syntax_error(char *prompt);
int		quote_opening(char *prompt);
void	check_quote(int *quote, char *c, int *i, int action);

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
char	*update_arg(char *arg, int *i, char *new_arg, t_shell *shell);
char	*join_arg(char *new_arg, char *arg, int *i, int quote);
char	*get_env(char **env, char *input);

// heredoc
char	*handle_heredoc(char *arg, t_shell *shell);
char	*check_delimeter(char *delimeter, int *quoted_delimeter);
void	heredoc_input(int *fd, char *delimeter);
void	read_heredoc_input(int *fd, char **input);

// heredoc_utils
char	*update_input(char *input, t_shell *shell);
char	*join_input(char *new_input, char *input, int *i);
void	handle_heredoc_signal(int status, t_shell *shell);

// builtin.c
bool	is_builtin(char *cmd);
int		exec_builtin(char **cmd, t_shell *shell);

// builtin
int 	builtin_echo(char **argv, t_shell *shell);
int 	builtin_cd(char **argv, t_shell *shell);
int 	builtin_pwd(char **argv, t_shell *shell);
int 	builtin_export(char **argv, t_shell *shell);
int 	builtin_unset(char **argv, t_shell *shell);
int 	builtin_env(char **argv, t_shell *shell);
int 	builtin_exit(char **argv, t_shell *shell);

// env
char	**copy_env(char **env);
char	*get_env_name(char *env);
char	*get_env_value(char *env);
bool	is_env_name(char *name, t_shell *shell);
char	*set_new_env(char *s1, char c, char *s2);
void	update_env(char *name, char *value, bool add, t_shell *shell);
char	**extend_env_array(char **env, char *name, char *value);
char	*get_path(char *cmd, t_shell *shell);

// execution
void	parse_ast(t_node *ast, t_shell *shell);
void	execute_fork(t_node *ast, t_shell *shell);
void	execute_node(t_node *node, t_shell *shell);
void	execute_command(t_exec_node *exec_node, t_shell *shell);
void	execute_error(char	*cmd_path, t_exec_node *exec_node);

// setup
void	setup_pipe(t_pipe_node *pipe_node, t_shell *shell);
void	setup_redir(t_redir_node *redir_node, t_shell *shell);
void	setup_child(int *pipefd, t_node *node, t_shell *shell);

// free.c
void	free_ast(t_node *node);
void	free_redir_data(t_redir_node *r_node);
void	typecasting_node(t_node *node, t_redir_node **r_node,
			t_exec_node **e_node, t_pipe_node **p_node);
void	free_array(char **arr);

// init.c
t_node	*init_exec_node(void);
t_node	*pipe_node(t_node *left_node, t_node *right_node);
void	init_redir_node(t_redir_node *redir_node, int redir_type);
void	insert_node(t_node *node, t_redir_node *redir_node);

#endif