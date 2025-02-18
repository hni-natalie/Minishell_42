/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:02:19 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 12:35:24 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
1. Remember to check for edge cases
2. Malloc enough spaces
3. Remember to check whether the pointer is pointing to something
4. If not, then return NULL
5. Assign zero to each positions
*/

/**
 * @brief function that allocate memory 
 * 
 * @param count how many empty block need to be created
 * @param size the size of each of the block
 * 
 * @return a pointer to allocated memory 
 * @return NULL pointer if there is an error
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count && count > UINT_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

/* int main(void)
{
	int	*ptr;
	int	n;
	int	i;
	n = 5;
	ptr = (int*)ft_calloc(n, sizeof(int));
	if (ptr == NULL)
	{
		printf("Memory not allocated. \n");
		exit (0);
	}
	else
	{
		printf("Memory succesfully allocated. \n");
		for(i = 0; i < n; ++i)
		{
			ptr[i] = i + 1;
			printf("%d, ", ptr[i]);
		}
	}
	free(ptr);
	return (0);
} */