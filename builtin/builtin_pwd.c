/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:20:41 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/14 16:47:57 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	PWD
	DESC: Prints working directory (absolute path; /home/user/projects)
	
	**PATH_MAX : prevents overflow, set standard limit
*/

int	builtin_pwd(char **argv, t_shell *shell)
{
	char	pwd[PATH_MAX];

	if (argv[1] == NULL)
	{
		if (getcwd(pwd, sizeof(pwd)))
		{
			printf("%s\n", pwd);
			shell->last_exit_status = SUCCESS;
		}
		else
		{
			shell->last_exit_status = FAILURE;
			perror("pwd");
		}
	}
	else
		shell->last_exit_status = FAILURE;
	return (shell->last_exit_status);
}