/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/03/07 23:45:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ECHO (with option -n)
	DESC: prints arg/s to stdout, seperated by space
		: should handle -n; suppress trailing n/l
*/

static void	print_arguments(char **argv, int *i, t_shell *shell)
{
	int	j;

	while (argv[*i])
	{
		j = -1;
		while (argv[*i][++j])
		{
			if (argv[*i][j] == '\\' && shell->argv_with_qoutes == 0)
				continue ;
			write(1, &argv[*i][j], 1);
		}
		if (argv[(*i) + 1])
			write(1, " ", 1);
		(*i)++;
	}
}

int	builtin_echo(char **argv, t_shell *shell)
{
	int		i;
	bool	suppress_n;

	if (!argv || !shell)
	{
		shell->last_exit_status = SUCCESS;
		return (shell->last_exit_status);
	}
	i = 0;
	suppress_n = false;
	while (argv[++i] && argv[i][0] == '-' && argv[i][1] == 'n'
		&& ft_strspn(argv[i] + 1, "n") == ft_strlen(argv[i]) - 1)
		suppress_n = true;
	print_arguments(argv, &i, shell);
	if (!argv[i] && !suppress_n)
		write(1, "\n", 1);
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}
