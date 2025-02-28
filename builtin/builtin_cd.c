/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/28 10:30:49 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	CD (with only a relative of absolute path)
	DESC: Change current working directory in a shell

	cd		; go to home directory 
	cd <dir>; move to specified directory
	cd -	; go to previous directory 
	cd ~ 	; go to home directory

*/

/*
	DESC: Search for env var by its (1)name, returns corresponding (2)directory
		- EG: var = OLDPWD, directory = /home/rraja-az/Desktop/Minishell
		- EG: VAR/NAME=VALUE
		- compares exactly and and make sure *env[len] is = > return after =
*/

static int	update_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (FAILURE);
	update_env("PWD", pwd, NO, shell);
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
	update_env("OLDPWD", oldpwd, NO, shell);
	home = get_directory("HOME", shell);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (FAILURE);
	}
	if (chdir(home) == 0)
	{
		update_env("PWD", home, NO, shell);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	prev_directory(t_shell *shell)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = get_directory("OLDPWD", shell);
	if (!oldpwd || chdir(oldpwd) == -1)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAILURE);
	printf("%s\n", cwd);
	update_env("OLDPWD", get_directory("PWD", shell), NO, shell);
	update_env("PWD", cwd, NO, shell);
	free(cwd);
	return (SUCCESS);
}

static void	cd_error(char *directory)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(directory, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
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
	update_env("OLDPWD", get_directory("PWD", shell), NO, shell);
	if (chdir(argv[1]) == -1)
	{
		cd_error(argv[1]);
		shell->last_exit_status = FAILURE;
		return (shell->last_exit_status);
	}
	shell->last_exit_status = update_pwd(shell);
	return (shell->last_exit_status);
}
