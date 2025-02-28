/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:24:16 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/28 10:28:29 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	EXIT (with no options)
	DESC: Terminates shell process
		: It can take optional exit status arg

	no arg		; exit with last cmd exit status
	args = 1	; converts it to in and exit with that value
	args > 1	; returns error and NOT exit (if numeric)
	args > 1	; prints error msg and return failure status (if non numeric)
	non int arg	; prints error msg and return failure status (2 in Bash)
*/

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

//printf("%s%s%s\n", RED, "exit 👋 Bye ~", RESET);
int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_status;

	printf("exit\n");
	if (!argv[1])
		exit(0);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->last_exit_status = 2;
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (FAILURE);
	}
	exit_status = ft_atoi(argv[1]) % 256;
	shell->last_exit_status = exit_status;
	exit(exit_status);
}
