/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:42:44 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/08 10:42:48 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
It is used to search within a binary block of data, 
not limited to null-terminated strings
It can be used to search through any memory region, such as arrays or buffers
*/
// line 20 * is added in front of the const char to access the value
// in order to compare str and c
// (char *)str does not need to access the value just return the memory location

/**
 * @brief function that locate the first occurence of c in string s
 * 
 * @param *str the whole strings
 * @param c the character to find
 * @param n number of bytes to find for
 * 
 * @return a pointer to the byte located, or NULL if no such byte exists
 * within n bytes
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/* int main(void)
{
    int arr[] = {0, 1, 2, 3, 4, 5};
    int find = 1;
	int *result = (int *)ft_memchr(arr, find, 6*sizeof(int));
	if (result != NULL)
    	printf("%ld", (int *)ft_memchr(arr, find, 6*sizeof(int)) - arr);
	else
		printf("Not found");
	// it's commonly used to print the index of an element in an array or
	// to indicate the distance between two memory location 
} */
