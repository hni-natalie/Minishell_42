/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:44 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:29:48 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concept:
1. Check for edge cases
2. Loop the lst and move it to last node
3. Return lst 
*/

/**
 * @brief funtion that get the last element of the list
 * 
 * @param *lst the start of the list
 * 
 * @return the last element of the list
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst->next;
	return (lst);
}

/* int main(void)
{
    t_list  *node1 = ft_lstnew("Hello");
    t_list  *node2 = ft_lstnew("Nice");
    t_list  *node3 = ft_lstnew("To");
    t_list  *node4 = ft_lstnew("Meet");
    t_list  *node5 = ft_lstnew("You");
    node1 -> next = node2;
    node2 -> next = node3;
    node3 -> next = node4;
    node4 -> next = node5;
    t_list  *last = ft_lstlast(node1);
    printf("%s", last->content);
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
} */
