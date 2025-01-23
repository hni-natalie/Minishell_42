/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:26:35 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:55 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concept:
1. initialise a variable to count the number of nodes 
2. loop the lst
3. link the lst to its next node
4. increment the count and return the count
*/

/**
 * @brief function that return the number of nodes in the list 
 * 
 * @param *lst start of the list
 * 
 * @return the number of new content added into the list
*/
int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/* int main(void)
{
	t_list	*lst = NULL;
	int size = ft_lstsize(lst);
	printf("%d\n", size);

	t_list	*head = NULL;
	t_list	*lst1 = ft_lstnew("Hello");
	t_list	*lst2 = ft_lstnew("My name is ");
	t_list	*lst3 = ft_lstnew("Natalie");
	ft_lstadd_front(&head, lst3);
	ft_lstadd_front(&head, lst2);
	ft_lstadd_front(&head, lst1);
	int	size1 = ft_lstsize(head);
	printf("%d", size1);
} */
