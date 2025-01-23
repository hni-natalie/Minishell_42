/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:33:22 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/12 17:33:53 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that add a new node at the end of the list
 * 
 * @param **lst pointer address of the first element of the list
 * @param *new pointer address of the new element to add to the list
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

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
		printf("%s ", current->content);
		current = current->next;
	}
	printf("\n");
	ft_lstclear(&head, del);
}
 */