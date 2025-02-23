/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:24:16 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/23 14:14:17 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	DESC: Terminates shell process. It can take optional exit status arg
		1. No arg - exit with last cmd exit status
		2. 1 arg - converts it to in and exit with that value
		3. Multiple args - return error and NOT exit
		4. Non numeric arg - Print error msg and return failure status (2 in Bash)

	FLOW:
		1. Check arg
			- more than 1 arg > print error > return (dont exit)
			- 1 arg > check if valid int > false; return 2 
		2. Determine exit status
			- no arg > use shell->last_exit_status as exit code
			- if arg given > convert to int and use that exit code
		3. Clean up resources
			- free shell->env
			- close file descriptors
		4. Exit shell
			- call exit(exit_status) to terminate the process
*/

// skip leading whitespace
// if cmd starts with + or -, move index forward
	// if cmd is empty after sign > return false
	// for each char in cmd, of if not numeric > return false
	// return true
static bool	is_numeric(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
			i++;
	if (s[i] == '\0')
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_status;
	
	printf("exit\n");
	if (argv[1] && argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			shell->last_exit_status = 2;
			exit(2);
		}
		exit_status = ft_atoi(argv[1]) % 256;
		shell->last_exit_status = exit_status;
	}
	else
		exit_status = shell->last_exit_status;
	exit(exit_status);
}
