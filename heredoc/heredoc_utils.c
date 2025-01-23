/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:08:21 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/23 13:08:57 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	handle_heredoc_signal(int status, t_shell *shell)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			shell->last_exit_status = 130;
	}
	else
		shell->last_exit_status = WEXITSTATUS(status);
}

