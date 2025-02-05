/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:59:01 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/05 10:38:32 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_line(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
		if (!ft_isspace(prompt[i]))
			return (0);
	return (free(prompt), 1);
}

int	syntax_error(char *prompt)
{
	int		i;
	int		tok;
	int		prev_tok;

	i = 0;
	tok = 1;
	prev_tok = 1;
	if (quote_opening(prompt))
		return (print_error(QUOTE_ERROR, prompt), 1);
	while (prompt[i])
	{
		prev_tok = tok;
		tok = grab_token(prompt, &i, NULL);
		if ((tok == '|' && prev_tok != 'w') || (tok == '|' && prev_tok == '|'))
			return (print_error(PIPE_ERROR, prompt), 1);
		else if (ft_strchr("<ha>", prev_tok) && tok == ';')
			return (print_error(SEMICOLON_ERROR, prompt), 1);
		else if (ft_strchr("<ha>", prev_tok) && ft_strchr("<ha>", tok))
			return (print_error(REDIR_ERROR, prompt), 1);
	}
	if (tok == '|')
		return (print_error(PIPE_ERROR, prompt), 1);
	else if (ft_strchr("<ha>", tok))
		return (print_error(NEWLINE_ERROR, prompt), 1);
	return (0);
}

int	quote_opening(char *prompt)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (prompt[++i])
	{
		if (!quote && (prompt[i] == '\'' || prompt[i] == '\"'))
			quote = prompt[i];
		else if (quote == prompt[i])
			quote = 0;
		// printf("quote: %d\n", quote); // debug
	}
	if (quote)
		return (1);
	return (0);
}

void	check_quote(int *quote, char *arg, int *i, int action)
{
	if (action == OPEN_QUOTE)
	{
		*quote = arg[*i];
		(*i)++;
	}
	else if (action == CLOSE_QUOTE)
	{
		*quote = 0;
		(*i)++;
	}
}
