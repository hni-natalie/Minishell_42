/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/08 17:51:30 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../include/minishell.h"

/* 
	ECHO
	DESC: prints arg to stdout, seperated by sapce
		: should handle -n; suppress trailing n/l
		: should escape sequence if required

	FLOW:
		1. Parse args
			- Iterate arg passed to echo
			- Check if first arg is -n > true > set flag to suppress newline
			- Skip -n if it is present
		2. Print arg
		3. Handle newline
			- if -n flag not set > prints newline at end
			- if -n flag > set > skip newline
		// NECESSARY? 
		4. Edge cases
			- no args
			- ensure multiple spaces btw args are preserved as per input
		5. Handle escape sequence
			- parse arg and replace sequence with corresponding char > \n & \t
		6. Set exit status?
		
*/

int	builtin_echo(char **cmd, t_shell *shell)
{
	int		i;
	bool	suppress;
	
	// check for -n option
	i = 1;
	suppress = false;
	while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		suppress = true;
		++i;
	}
	// iterate through remaining args
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(args[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	// print newline unless -n is set
	if (!cmd[1] && !suppress)
		write (1, "\n", 1);
	// set exit status
	shell->last_exit_status = 0;
	return (shell->last_exit_status);
}

