/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:01:12 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/11 19:01:50 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Concept:
1. check for edge cases
2. we need to link new with the lst and put new in the front
3. we move lst to new->next
4. let new be the first link of a list
*/

/**
 * @brief function that add a new element at the front of the list 
 * 
 * @param **lst pointer address to the first element of the list
 * @param *new pointer address of the new element to add to the list
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/* int main(void)
{
	int a = 4;
	int b = 5;
	int c = 6;
	// first create a empty list 
	t_list *head = NULL;
	t_list *node1 = ft_lstnew(&a);
	t_list *node2 = ft_lstnew(&b);
	t_list *node3 = ft_lstnew(&c);
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);
	t_list *current = head;
	while (current != NULL)
	{
		printf("%d ", *(int *)(current->content));
		current = current->next;
	}
	free(node1);
	free(node2);
	free(node3);

	return (0);
}
 */