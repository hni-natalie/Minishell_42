/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:19:43 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/22 13:19:24 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	grab_token(char *prompt, int *idx, char *word_in_tok)
{
	int token;
	int start_tok;
	int end_tok;
	
	while (prompt[*idx] && ft_isspace(prompt[*idx]))
		(*idx)++;
	start_tok = *idx;
	token = prompt[*idx];
	label_token(prompt, &token, idx);
	end_tok = *idx;
	while (prompt[*idx] && ft_isspace(prompt[*idx]))
		(*idx)++;
	if (word_in_tok)
		ft_strlcpy(word_in_tok, &prompt[start_tok], 
			end_tok - start_tok + 1);
	return (token);
}

void	label_token(char *prompt, int *token, int *idx)
{
	if (prompt[*idx] == 0)
		return ;
	else if (prompt[*idx] == '|')
		(*idx)++;
	else if (prompt[*idx] == ';')
		(*idx)++;
	else if (prompt[*idx] == '<' || prompt[*idx] == '>')
	{
		(*idx)++;
		if (prompt[*idx] == '<' && prompt[*idx - 1] == '<')
		{
			*token = 'h';
			(*idx)++;
		}
		else if (prompt[*idx] == '>' && prompt[*idx - 1] == '>')
		{
			*token = 'a';
			(*idx)++;
		}
	}
	else
		word_token(prompt, token, idx);
}

void	word_token(char *prompt, int *token, int *idx)
{
	int	quote;

	quote = 0;
	*token = 'w';
	while (prompt[*idx])
	{
		if (!quote && (prompt[*idx] == '\'' ||
			prompt[*idx] == '\"'))
			quote = prompt[*idx];
		else if (quote == prompt[*idx])
			quote = 0;
		else if (!quote && (ft_isspace(prompt[*idx])
			|| ft_strchr("<>|", prompt[*idx])))
			break ;
		(*idx)++;
	}
}
