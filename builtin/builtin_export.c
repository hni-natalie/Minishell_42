/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:06:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/28 10:31:15 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	EXPORT (with no options)
	DESC: Create / modify env and make them available to child process
*/

static void	print_export_error(char *argv)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(argv, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static void	handle_without_equal(char *argv, t_shell *shell)
{
	if (!argv[0] || !is_valid_env_name(argv))
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	if (!is_env_name(argv, shell->env))
		shell->export_env = extend_env_array(shell->export_env, argv, NULL);
	shell->last_exit_status = SUCCESS;
}

static void	handle_with_equal(char *equal, char *argv, t_shell *shell)
{
	char	name[PATH_MAX];
	char	*value;

	if (equal == argv)
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	ft_strlcpy(name, argv, equal - argv + 1);
	if (!name[0] || !is_valid_env_name(name))
	{
		print_export_error(argv);
		shell->last_exit_status = FAILURE;
		return ;
	}
	value = equal + 1;
	update_env(name, value, YES, shell);
	shell->last_exit_status = SUCCESS;
}

int	builtin_export(char **argv, t_shell *shell)
{
	int		i;
	char	*equal;

	if (!argv[1])
	{
		sort_export_env(shell->export_env);
		print_export_env(shell);
		shell->last_exit_status = SUCCESS;
		return (shell->last_exit_status);
	}
	i = 0;
	while (argv[++i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal)
			handle_with_equal(equal, argv[i], shell);
		else
			handle_without_equal(argv[i], shell);
	}
	return (shell->last_exit_status);
}
