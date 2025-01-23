/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:50:20 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/19 12:58:07 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concept:
1. Check for edge cases
2. If there is something in lst
3. delete the content in the lst
4. free the node 
*/

/**
 * @brief function that removes content in one node from the list
 * 
 * @param *lst the element to free
 * @param del address of the function that can delete the element's content
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

/* void	del(void *content)
{
	(void)content;
}
// Since content is just an integer pointer, no need to free it 
// if content was dynamically allocated, you would free it here

int main(void)
{
	int a = 4;
	int b = 5;
	int c = 6;
	t_list *node1 = ft_lstnew(&a);
	t_list *node2 = ft_lstnew(&b);
	t_list *node3 = ft_lstnew(&c);
	t_list *head = NULL;
	head = node1;
	node1->next = node2;
	node2->next = node3;
	ft_lstdelone(node2, del);
	node1->next = node3;
	t_list *current = head;
	while (current != NULL)
	{
		printf("%d ", *(int *)(current->content));
		current = current->next;
	}
	ft_lstdelone(node1, del);
	ft_lstdelone(node3, del);

	return (0);
}
 */