/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:32:18 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:37:05 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concept:
1. Check for edge cases
2. Initialise a variable for new_list 
3. Initialise a variable for new_obj
4. make sure the new_list is empty
5. Loop through the linked list 
6. new_obj is formatted content in each node
7. if new_obj is NULL, then clear it 
8. add the new_obj into new_list
9. return the new_list 
*/

/**
 * @brief function that creates a new list resulting 
 	from the application of f to each element
 * 
 * @param *lst pointer address to one element
 * @param f the address of the function to apply
 * @param del the address of the function that can delete an element's content
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_obj;

	if (!f || !lst || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_obj = ft_lstnew((*f)(lst->content));
		if (!new_obj)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_obj);
		lst = lst->next;
	}
	return (new_list);
}

/* void	*duplicate_content(void *content)
{
	char	*new_content = strdup((char *)content);
	return (new_content);
}

void	del(void *content)
{
	free(content); // strdup allocate memory that must be freed
}

int main(void)
{
 	t_list	*head = NULL;
	t_list	*lst1 = ft_lstnew(strdup("Hello"));
	t_list	*lst2 = ft_lstnew(strdup("My name is"));
	t_list	*lst3 = ft_lstnew(strdup("Natalie"));
	ft_lstadd_back(&head, lst1);
	ft_lstadd_back(&head, lst2);
	ft_lstadd_back(&head, lst3);
	t_list	*mapped_list = ft_lstmap(head, duplicate_content, del);
	t_list *current = head;
	while (current)
	{
		printf("%s ", current->content);
		current = current->next;
	}
	printf("\n");
	current = mapped_list;
	while (current)
	{
		printf("%s ", current->content);
		current = current->next;
	}
	ft_lstclear(&head, del);
	ft_lstclear(&mapped_list, del);
} */