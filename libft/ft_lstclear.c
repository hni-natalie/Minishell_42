/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:47:24 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:37:53 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that removes the element passes as parameter 
 	and all the following elements
 * 
 * @param **lst pointer address to one element 
 * @param del address of the function that can delete the element's content
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		free((*lst));
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

/* void	del(void *content)
{
	(void)content; // No action needed for string literals
} */

/* int main(void)
{
 	t_list	*head = NULL;
	t_list	*lst1 = ft_lstnew("Hello");
	t_list	*lst2 = ft_lstnew("My name is");
	t_list	*lst3 = ft_lstnew("Natalie");
	ft_lstadd_back(&head, lst1);
	ft_lstadd_back(&head, lst2);
	ft_lstadd_back(&head, lst3);
	t_list *current = head;
	while (current != NULL)
	{
		printf("%s ", (char *)current->content);
		current = current->next;
	}
	printf("\n");
	ft_lstclear(&head, del);
	if (head == NULL)
	{
		printf("List cleared successfully");
	}
}
 */