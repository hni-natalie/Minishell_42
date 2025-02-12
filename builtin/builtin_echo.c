/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/12 08:59:53 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../include/minishell.h"

/* 
	ECHO
	DESC: prints arg to stdout, seperated by sapce
		: should handle -n; suppress trailing n/l

	FLOW:
		1. Parse args
			- Iterate arg passed to echo
			- Check if first arg is -n && multiple -n flags
				**ft_strspn returns length of initial part of str that contains only chars from accept
				**ft_strspn(const char *str, const char *accept)
				**ft_strspn(args[i] + 1, "n") > whatever after '-'
				** == ft_strlen(args[i]) - 1) > length after '-'
				> true > set flag to suppress newline
		2. Print arg
		3. Check if no arg and supress not flagged
		5. Return exit status
*/

int	builtin_echo(char **args, t_shell *shell)
{
	int		i;
	bool	suppress_n;
	
	i = 1;
	suppress_n = false;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0
		&& ft_strspn(args[i] + 1, "n") == ft_strlen(args[i]) - 1)
	{
		suppress_n = true;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!args[i] && !suppress_n)
		write (1, "\n", 1);
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}

