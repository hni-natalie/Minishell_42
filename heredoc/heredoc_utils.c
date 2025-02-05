/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:08:21 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/26 18:43:39 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_delimeter(char *delimeter, int *quoted_delimeter)
{
	char	*new_delimeter;
	
	if (delimeter[0] != '\'' && delimeter[0] != '\"')
		return (delimeter);
	*quoted_delimeter = YES;
	new_delimeter = ft_substr(delimeter, 1, ft_strlen(delimeter) - 2);
	return (new_delimeter);
}

char	*update_input(char *input, t_shell *shell)
{
	int		i;
	char	*new_input;

	i = 0;
	new_input = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
			new_input = update_arg(input, &i, new_input, shell);
		else
			new_input = join_input(new_input, input, &i);
	}
	free(input);
	return (new_input);
}

char	*join_input(char *new_input, char *input, int *i)
{
	int start;
	char *append_new_input;

	start = *i;
	while (input[*i])
	{
		if (input[*i] == '$')
			break ;
		(*i)++;
	}
	append_new_input = ft_substr(input, start, *i - start);
	new_input = ft_strjoin(new_input, append_new_input);
	free(append_new_input);
	return (new_input);
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

