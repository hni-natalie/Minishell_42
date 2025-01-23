/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:11:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/11 19:02:41 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s1.num shows that s1 is a structure 
// s1->num shows that s1 is a pointer to a structure 
// t_list represents a structure type, which in this case
// likely represents a node in a linked list 

/* 
Concept:
1. create a new block to hold the new content at the end 
2. allocate memory for it 
3. assign stuff into content and next 
4. return the new block
*/

/**
 * @brief function that create a new list node element
 * 
 * @param *content the content of the new element
 * 
 * @return new element
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	t_list *node1 = ft_lstnew(&a);
	t_list *node2 = ft_lstnew(&b);
	t_list *node3 = ft_lstnew(&c);
	node1->next = node2;
	node2->next = node3;
	t_list *current = node1;
	while (current != NULL)
	{
		printf("%d ", *(int *)(current->content));
		current = current->next;
	}
	free(node1);
	free(node2);
	free(node3);

	return (0);
} */
