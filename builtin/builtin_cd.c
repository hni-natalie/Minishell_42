/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/08 17:28:41 by rraja-az         ###   ########.fr       */
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
	cd ..	; move up one directory (parent directory)
	cd . 	; does nothing, stays in same directory
	cd /	; go to root directory
	**cd ~ 	; go to home directory > prints new prompt

*/

// DESC	: Search for env var by its (1)key, returns corresponding (2)directory
// 	- EG: key = PATH, directory = /usr/bin
//	- EG: KEY=VALUE
char	*get_directory(char *key, t_shell *shell)
{
	int	i;
	int	key_len;
	
	if (!key || !shell || !shell->env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0 && shell->env[i][key_len] == '=')
			return (shell->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int update_pwd(t_shell *shell)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	//update_env("PWD", pwd, false, shell);
	free(pwd);
	return (0);
}

/*
	DESC: Change to home directory and update oldpwd
	
	1. Get home directory
	2. check if home is null ? home is not set? set home then?
	3. get current directory
	4. if chdir home is true > update pwd
	5. Return success or failure
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
	// update oldpwd and pwd > insert update pwd function here
	// update_env("OLDPWD", get_directory("PWD", shell), bool, shell);
	if (chdir(home) == 0)
	{
		// update env("PWD", home, false, shell);
		return (0);
	}
	return (1);
}

/*
	DESC: Change to previous directory and update old pwd
	
	1. get oldpwd
	2. if oldpwd is null or fails > return 1
	3. update env (update pwd with oldpwd)
	4.return 0
*/
int prev_directory(t_shell *shell)
{
	char *oldpwd;

	oldpwd = get_directory("OLDPWD", shell);
	if (!oldpwd || chdir(oldpwd) == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	// update pwd after switching to old pwd
	// update_env("PWD", oldpwd, false, shell);
	return (0);
}

/*
	DESC: Checks args and determine directory
	
	1. Get current working directory
	2. Check if directory is valid
	3. If valid > update pwd
	4. Return exit code
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
		printf("minishell: cd : %s: No such file or directory\n", path);
		shell->last_exit_status = 1;
		return (shell->last_exit_status);
	}
	// if successfull > update environment variable > insert update env fx here
	// update_env("OLDPWD", oldpwd, bool(false), shell);
	shell->last_exit_status = change_pwd(shell);
	return (shell->last_exit_status);
}

/* 
// check validity of directory
int	is_directory(char *path)
{
	DIR *dir;

	if (!path)
		return (0);
	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

//change directory ; checks for errors, prints error message
int	change_directory(char *path)
{
	if (!path)
		return (-1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

// update directory
int update_directory(t_shell *shell)
{
	char cwd[1024];
	
	if (!shell || !shell->env)
		return (-1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (-1);
	}
} */