/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:22:08 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/27 15:22:16 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_arg(char **argv, t_shell *shell)
{
	char	*new_arg;
	int		i;

	i = -1;
	while (argv[++i])
	{
		new_arg = check_arg(argv[i], shell);
		free(argv[i]);
		argv[i] = new_arg;
	}
}

/*
	reason why we need to use join_arg
		as we go through the entire arg character by character
		we need to join the characters together to form a new_arg 
		then only return the new_arg
*/
char	*check_arg(char *arg, t_shell *shell)
{
	char	*new_arg;
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	if (ft_strcmp(arg, "\0") == 0)
		return (arg);
	new_arg = ft_strdup("");
	while (arg[i] && i < (int)ft_strlen(arg))
	{
		if (!quote && (arg[i] == '\'' || arg[i] == '\"'))
			check_quote(&quote, arg, &i, OPEN_QUOTE);
		else if (quote == arg[i])
		{
			check_quote(&quote, arg, &i, CLOSE_QUOTE);
			shell->argv_with_qoutes = 1;
		}
		else if (arg[i] == '$' && (quote == '\"' || !quote))
			new_arg = update_arg(arg, &i, new_arg, shell);
		else
			new_arg = join_arg(new_arg, arg, &i, quote);
	}
	return (new_arg);
}

char	*join_arg(char *new_arg, char *arg, int *i, int quote)
{
	int		start;
	char	*append_new_arg;
	char	*new_joined_arg;

	start = *i;
	new_joined_arg = NULL;
	while (arg[*i])
	{
		if ((!quote && (arg[*i] == '\'' || arg[*i] == '\"'
					|| arg[*i] == '$')) || (quote == '\'' && arg[*i] == quote)
			|| (quote == '\"' && (arg[*i] == quote || arg[*i] == '$')))
			break ;
		(*i)++;
	}
	append_new_arg = ft_substr(arg, start, *i - start);
	new_joined_arg = ft_strjoin(new_arg, append_new_arg);
	free(new_arg);
	free(append_new_arg);
	return (new_joined_arg);
}
