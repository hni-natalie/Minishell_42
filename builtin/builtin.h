/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:57:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/12 15:07:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <limits.h>
# include <stdbool.h>

typedef	struct 		s_shell t_shell;

/*					VALIDATE & EXEC					*/
bool				is_builtin(const char *cmd);
int					exec_builtin(char **cmd, t_shell *shell);

/*					BUILT-INS						*/
// return type should be int because they return exit status/code
int 				builtin_echo(char **args, t_shell *shell);
int 				builtin_cd(char **args, t_shell *shell);
int 				builtin_pwd(char **args, t_shell *shell);
int 				builtin_export(char **args, t_shell *shell);
int 				builtin_unset(char **args, t_shell *shell);
int 				builtin_env(char **args, t_shell *shell);
int 				builtin_exit(char **args, t_shell *shell, t_node *ast);

#endif

/*
typedef struct 		s_builtin
{
	char			*cmd;
	int				(*func)(char **cmd, t_shell *shell);
}					t_builtin;

/*
	DESC: Function Pointer Type
	- t_builtin_func represents a function signature
		- what is function pointer? var that stores &function
		- allows to call function dynamically
	- PARAM : arr of args and shell state (env, exit code)
	- RETURN : exit status 
*/
/* typedef	int	(*t_builtin_ft)(char **args, t_shell *shell);

//					DATA STRUCT				
typedef	enum		e_builtin
{
					builtin_echo,
					builtin_cd,
					builtin_pwd,
					builtin_export,
					builtin_unset,
					builtin_env,
					builtin_exit,
					builtin_count
}
					t_builtin;

// for function opendir & closedir
// opendir ; opens dir stream and returns pointer to DIR structure
// closedir; closes dir stream once done using it
# include <dirent.h>
*/