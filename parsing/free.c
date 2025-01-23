/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:25:16 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/23 14:59:05 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	free_ast(r_node->next);	
		act as a recursive function to free the next node
*/
void	free_ast(t_node *node)
{
	t_redir_node	*r_node;
	t_exec_node		*e_node;
	t_pipe_node		*p_node;

	if (!node)
		return ;
	typecasting_node(node, &r_node, &e_node, &p_node);
	printf("free -- node->type: %d\n", node->type);
	if (node->type == PIPE)
	{
		free_ast(p_node->left);
		free_ast(p_node->right);
		free(p_node);
	}
	else if (node->type == REDIR)
	{
		free_ast(r_node->next);
		free_redir_data(r_node);
		free(r_node);
	}
	else if (node->type == EXEC)
	{
		free_arr(e_node->argv);
		free(e_node);
	}
}

void	typecasting_node(t_node *node, t_redir_node **r_node,
	t_exec_node **e_node, t_pipe_node **p_node)
{
	if (r_node)
		*r_node = (t_redir_node *)node;
	if (e_node)
		*e_node = (t_exec_node *)node;
	if (p_node)
		*p_node = (t_pipe_node *)node;
}

void	free_redir_data(t_redir_node *r_node)
{
	if (r_node->file)
		free(r_node->file);
	if (r_node->heredoc)
	{
		printf("free -- r_node->heredoc\n");
		free(r_node->heredoc);
	}
}
