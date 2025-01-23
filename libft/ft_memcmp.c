/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:30:57 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/08 11:31:03 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_memcmp can be used to compare array and buffer
	ft_strncmp can only used to compare str
	ft_memcmp compare the block of memory byte by byte */

/**
 * @brief function compare s1 and s2 over n number of bytes
 * @param *ptr1 
 * @param *ptr2
 * @param n number of byte to compare 
 * 
 * @return 0 if there are the same
 * @return the difference betweeen the first two differing bytes
 */
int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) ptr1;
	str2 = (const unsigned char *) ptr2;
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

/* int main(void)
{
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {1, 2, 3, 3, 7};
	printf("%d", ft_memcmp(arr1, arr2, 3*sizeof(int)));
} */