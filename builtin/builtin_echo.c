/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/24 14:50:51 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
	ECHO
	DESC: prints arg to stdout, seperated by sapce
		: should handle -n; suppress trailing n/l

	FLOW:
		1. Parse args
			- Iterate arg passed to echo
			- Check if first arg is -n && multiple -n flags
				**ft_strspn(args[i] + 1, "n") > whatever after '-'
				** == ft_strlen(args[i]) - 1) > length after '-'
				> true > set flag to suppress newline
		2. Print arg
		3. Check if no arg and supress not flagged
		5. Return exit status
*/

static void	print_arguments(char **argv, int *i, t_shell *shell)
{
	int	j;

	while (argv[*i])
	{
		j = -1;
		// printf("argv_with_qoutes: %d\n", shell->argv_with_qoutes); // debug
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
	
	i = 0;
	suppress_n = false;
	while (argv[++i] && argv[i][0] == '-' && argv[i][1] == 'n' 
		&& ft_strspn(argv[i] + 1, "n") == ft_strlen(argv[i]) - 1)
		suppress_n = true;
	print_arguments(argv, &i, shell);
	if (!argv[i] && !suppress_n)
		write (1, "\n", 1);
	shell->last_exit_status = SUCCESS;
	return (shell->last_exit_status);
}


