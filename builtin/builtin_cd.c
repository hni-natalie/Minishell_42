/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/21 09:56:40 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	CD (with only a relative of absolute path)
	DESC: Change current working directory in a shell
	
	1. Check args
		- if no arg > change to home dir 
		- arg > check the path
	2. Handle target path
		- if path is - (prev dir) > cd to prev dir
		- if relative path (full path starting from root /) > check validity
			-EG : cd /home/user/Documents
		- if absolute path (without leading /) > check validity
			-EG : cd Documents
	3. Validate the path
		- Check if dir exist
		- Check error (invalid dir)

	cd		; go to home directory > prints new prompt
	cd <dir>; move to specified directory
	cd -	; go to previous directory > 
			; if oldpwd is not set > print error
			; if successful, print new path (pwd output)
	**cd ~ 	; go to home directory > prints new prompt

*/

/* 
	DESC: Search for env var by its (1)name, returns corresponding (2)directory
		- EG: var = OLDPWD, directory = /home/rraja-az/Desktop/Minishell
		- EG: VAR/NAME=VALUE
		- compares exactly and and make sure *env[len] is = > return after =
*/
static char	*get_directory(char *var, t_shell *shell)
{
	int		var_len;
	char	**env;

	if (!var || !shell || !shell->env)
		return (NULL);
	var_len = ft_strlen(var);
	env = shell->env;
	while (*env)
	{
		if (ft_strncmp(*env, var, var_len) == 0 && (*env)[var_len] == '=')
			return (*env + var_len + 1);
		env++;
	}
	return (NULL);
}

/*
	DESC: handles all pwd and oldpwd updates
	
	1. Get current directory (PWD)
		- getcwd(char *buf, size_t size) 
		- NULL 	; we're not providing our required buffer
		- 0		; malloc for buffer
		- since its NULL,0 > getcwd auto mallocs required size for dir path
		- thus we need to FREE after using it
	2. Get old working directory (OLDPWD)
		- if oldpwd is not null > update the oldpwd
	3. Else, update the pwd to current dir
	4. Free pwd (cz getcwd previously malloc)
*/
static int update_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (FAILURE);
	update_env("PWD", pwd, false, shell);
	free(pwd);
	return (SUCCESS);
}

static int	home_directory(t_shell *shell)
{
	char	*home;
	char	*oldpwd;

	oldpwd = get_directory("PWD", shell);
	if (!oldpwd)
		oldpwd = "";
	update_env("OLDPWD", oldpwd, false, shell);
	home = get_directory("HOME", shell);
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (FAILURE);
	}
	if (chdir(home) == 0)
	{
		update_env("PWD", home, false, shell);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int prev_directory(t_shell *shell)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = get_directory("OLDPWD", shell);
	if (!oldpwd || chdir(oldpwd) == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAILURE);
	printf("%s\n", cwd);
	update_env("OLDPWD", get_directory("PWD", shell), false, shell);
	update_env("PWD", cwd, false, shell);
	free(cwd);
	return (SUCCESS);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	if (argv[1] == NULL || argv[1][0] == '~')
	{
		shell->last_exit_status = home_directory(shell);
		return (shell->last_exit_status);
	}
	if (argv[1][0] == '-')
	{
		shell->last_exit_status = prev_directory(shell);
		return (shell->last_exit_status);
	}
	update_env("OLDPWD", get_directory("PWD", shell), false, shell);
	if (chdir(argv[1]) == -1)
	{
		printf("minishell: cd : %s: No such file or directory\n", argv[1]);
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
	shell->last_exit_status = update_pwd(shell);
	return (shell->last_exit_status);
}

// hello, hi