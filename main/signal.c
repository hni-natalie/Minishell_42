/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:51:50 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/05 13:49:03 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  
	rl_on_new_line()
		prepares the terminal to start with a clean new line
	rl_replace_line("", 0)
		clears the current line in readline
	rl_redisplay()
		redraws the prompt and the current line
*/
void	sigint_handler(int signum)
{
	(void) signum;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint(t_shell *shell)
{
	shell->last_exit_status = 130;
	g_signal = 0;
}

void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
}

