/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:24:16 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/07 21:21:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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

	// set sign to 1
	// skip leading whitespace
	// if cmd starts with '-', set sign = -1 and move index
	// if cmd starts with '+', move index
	// init result to 0
	// iterate args
		// 
	// return (result * sign) % 256
		// WHY? because exit code ends at 255
static int	exit_toi(char *s)
{
	int	sign;
	int result;
	
	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s == '\0' || !(*s >= '0' && *s <= '9'))
		{
			printf("Error: Exit code must be numeric\n");
			// clean entire shell
			exit(2); // update last_exit_status?
		}
		result = result * 10 + (*s - '0');
		s++;
	}
	return ((result * sign) % 256);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_status;
	
	printf("exit\n");
	if (args[1] && args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			shell->last_exit_status = 2;
			free_shell(shell); // TODO
			exit(2);
		}
		exit_status = exit_toi(args[1]);
	}
	else
		exit_status = shell->last_exit_status;
	free_shell(shell);
	exit(exit_status);
}
