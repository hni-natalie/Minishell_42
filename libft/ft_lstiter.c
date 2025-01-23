/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:16:16 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:37:25 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that apply a function to each element's content
 * 
 * @param *lst pointer address to one element
 * @param f function to apply
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/* void	increment(void *content)
{
	int	*int_content = (int *)content;
	*int_content = *int_content * 2;
} */

/* int main(void)
{
	int a = 4;
	int b = 5;
	int c = 6;
	t_list *head = NULL;
	t_list *node1 = ft_lstnew(&a);
	t_list *node2 = ft_lstnew(&b);
	t_list *node3 = ft_lstnew(&c);
	ft_lstiter(node1, increment);
	ft_lstiter(node2, increment);
	ft_lstiter(node3, increment);
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