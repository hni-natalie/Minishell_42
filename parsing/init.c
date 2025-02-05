/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:38:35 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/03 11:06:54 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*pipe_node(t_node *left_node, t_node *right_node)
{
	t_pipe_node	*pipe_node;

	// printf("pipe_node\n");
	pipe_node = malloc(sizeof(t_pipe_node));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = PIPE;
	pipe_node->left = left_node;
	pipe_node->right = right_node;
	return ((t_node *)pipe_node);
}

t_node	*init_exec_node(void)
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->type = EXEC;
	node->argv = NULL;
	return ((t_node *)node);
}

void	init_redir_node(t_redir_node *redir_node, int redir_type)
{
	// printf("init_redir_node\n"); //debug
	ft_memset(redir_node, 0, sizeof(t_redir_node));
	redir_node->type = REDIR;
	if (redir_type == INPUT)
	{
		redir_node->mode = O_RDONLY;
		redir_node->fd = 0;
	}
	else if (redir_type == OUTPUT)
	{
		redir_node->mode = O_WRONLY | O_CREAT | O_TRUNC;
		redir_node->fd = 1;
	}
	else if (redir_type == APPEND)
	{
		redir_node->mode = O_WRONLY | O_CREAT | O_APPEND;
		redir_node->fd = 1;
	}
}

/*
	redir_node->next = tmp->next;
		let the tail of the redir_node link with node after tmp
	tmp->next = (t_node *)redir_node;
		let tmp link with the head of the redir_node
	head and tail of the redir_node are linked with the linked list 
	so that redir_node is completely inserted into the linked list 
*/
void	insert_node(t_node *node, t_redir_node *redir_node)
{
	t_redir_node *tmp;

	tmp = (t_redir_node *)node;
	while (tmp->next->type == REDIR)
		tmp = (t_redir_node *)tmp->next;
	redir_node->next = tmp->next;
	tmp->next = (t_node *)redir_node;
}
