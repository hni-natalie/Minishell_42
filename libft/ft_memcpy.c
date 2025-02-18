/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:22:09 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:32 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function copies n bytes from memory area src to memory area dest
 * if dest and src overlap, behavior is undefined
 * 
 * @param dest - the place to locate to
 * @param src - the words located
 * @param n - num of the words to copy
 * 
 * @return the original value of dst
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (dest);
	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

// int main(void)
// {
// 	const char src[50] = "Happy go Lucky";
// 	char dest[50] = "ByeBye Haha";
// 	printf("%s\n", dest);
// 	ft_memcpy(dest, src, 5);
// 	printf("%s", dest);
// }
// if want to copy the whole string from src, need to +1 for null terminator
