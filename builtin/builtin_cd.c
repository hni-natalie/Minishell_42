/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/11 11:36:36 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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
	DESC	: Search for env var by its (1)name, returns corresponding (2)directory
		- EG: var = PATH, directory = /usr/bin
		- EG: VAR=VALUE
		- compares exactly and and make sure *env[len] is = > return after =
*/
char	*get_directory(char *var, t_shell *shell)
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
int update_pwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	oldpwd = get_directory("PWD", shell);
	if (oldpwd)
		update_env("OLDPWD", oldpwd, false, shell);
	update_env("PWD", pwd, false, shell);
	free(pwd);
	return (0);
}

/*
	DESC: Change cwd to home directory and update env (pwd & oldpwd)
	
	1. Get home directory
	2. check if home is null ? home is not set? set home then?
	3. get current directory
	4. if chdir home is true > update pwd > else return 1
		- chdir return 0 (successful), -1 (error)
*/
int	home_directory(t_shell *shell)
{
	char *home;

	home = get_directory("HOME", shell);
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0)
		return (update_pwd(shell));
	printf("minishell: cd: %s: No such file or directory\n", home); // DISCUSS - necessary?
	return (1); 
}

/*
	DESC: Change to previous directory and update old pwd

	1. get oldpwd
	2. if oldpwd is null or fails > print error > return 1
	3. getcwd > print the current directory (same as bash)
*/
int prev_directory(t_shell *shell)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = get_directory("OLDPWD", shell);
	if (!oldpwd || chdir(oldpwd) == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	cwd = get(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (update_pwd(shell));
}

/*
	DESC: Checks args and determine directory
	
	1. Check if no arg or ~ > return to home
	2. Check if arg is - > return to prev dir
	3. Change dir based on arg > check for error
	4. cd-ed > return update_pwd
*/
int	builtin_cd(char **args, t_shell *shell)
{
	if (args[1] == NULL || args[1][0] == '~')
	{
		shell->last_exit_status = home_directory(shell);
		return (shell->last_exit_status);
	}
	if (args[1][0] == '-')
		return (prev_directory(shell));
	if (chdir(args[1]) == -1)
	{
		printf("minishell: cd : %s: No such file or directory\n", args[1]);
		shell->last_exit_status = 1;
		return (shell->last_exit_status);
	}
	return (update_pwd(shell));
}