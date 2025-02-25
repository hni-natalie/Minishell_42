/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:17:01 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/25 17:08:46 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_node(char *prompt, t_shell *shell)
{
	t_node	*node;
	int		i;
	int		token;
	char	arg[1024];
	
	i = 0;
	if (empty_line(prompt) || syntax_error(prompt))
		return (NULL);
	// printf("prompt in parse_node: %s\n", prompt); // debug
	node = parse_exec(prompt, &i, shell);
	token = grab_token(prompt, &i, arg);
	if (token == '|')
		node = pipe_node(node, parse_node(&prompt[i], shell));
	return (node);
}

t_node	*parse_exec(char *prompt, int *i, t_shell *shell)
{
	t_node		*node;
	t_exec_node	*exec_node;
	int			idx;
	char		arg[1024];
	
	idx = 0;
	node = init_exec_node();
	exec_node = (t_exec_node *)node;
	if (ft_strchr("<>", prompt[*i]))
		node = parse_redir(node, prompt, i, shell);
	malloc_argv(prompt, exec_node);
	while (prompt[*i] && prompt[*i] != '|')
	{
		grab_token(prompt, i, arg);
		exec_node->argv[idx] = ft_strdup(arg);
		// printf("exec_node->argv[%d]: %s\n", idx, exec_node->argv[idx]); // debug
		idx++;
		if (ft_strchr("<>", prompt[*i]))
			node = parse_redir(node, prompt, i, shell);
	}
	exec_node->argv[idx] = NULL;
	return (handle_arg(exec_node->argv, shell), node);
}

/*
	minus with redir_count bcs the word token after the redirection token
	is not considered as an argument
*/
void	malloc_argv(char *prompt, t_exec_node *exec_node)
{
	int	word_count;
	int	redir_count;
	int	i;
	int	token;
	
	i = 0;	
	word_count = 0;
	redir_count = 0;
	while (prompt[i])
	{
		token = grab_token(prompt, &i, NULL);
		if (token == 'w')
			word_count++;
		else if (ft_strchr("<ha>", token))
			redir_count++;
		else if (token == '|')
			break ;
	}
	exec_node->argv = malloc(sizeof(char *) * (word_count - redir_count + 1));
}

/*
	grab_token function is called the second time to get the argument
	after the redirection token
*/
t_node	*parse_redir(t_node *node, char *prompt, int *i, t_shell *shell)
{
	int		tok;
	char	arg[1024];
	
	while (ft_strchr("<>", prompt[*i]) && prompt[*i])
	{
		tok = grab_token(prompt, i, NULL);
		grab_token(prompt, i, arg);
		if (tok == '<')
			node = redir_node(arg, INPUT, node, shell);
		else if (tok == '>')
			node = redir_node(arg, OUTPUT, node, shell);
		else if (tok == 'a')
			node = redir_node(arg, APPEND, node, shell);
		else if (tok == 'h')
			node = redir_node(arg, HEREDOC, node, shell);
	}
	return (node);
}

/*
	typecast the redir_node to t_node at the end of the function
	so that it can stored in the linked list 

	if there is no redir_node in the linked list, 
	the redir_node will be the head of the linked list
	else the redir_node will be the next node in the linked list
*/
t_node	*redir_node(char *arg, int redir_type, t_node *node, t_shell *shell)
{
	t_redir_node	*redir_node;

	redir_node = malloc(sizeof(t_redir_node));
	init_redir_node(redir_node, redir_type);
	if (redir_type != HEREDOC)
		redir_node->file = check_arg(arg, shell);
	else
	{
		redir_node->heredoc = handle_heredoc(arg, shell);
		redir_node->mode = -1;
		redir_node->fd = -1;
	}
	// printf("redir_node->file: %s\n", redir_node->file); // debug
	// printf("redir_node->delimeter: %s\n", redir_node->heredoc); // debug
	if (node->type == REDIR)
	{
		// printf("redir_node->file: %s\n", redir_node->file); // debug
		return (insert_node(node, redir_node), node);
	}
	redir_node->next = node;
	return ((t_node *)redir_node);
}
