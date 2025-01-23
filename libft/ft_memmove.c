/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:51:26 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:26 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function copies len bytes from src to dst
 * two strings may overlap 
 * 
 * @param *dest - the words should be copied to 
 * @param *src - the words to copied from 
 * @param n - number of words that want to copy 
 * 
 * @return original value of dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = dest;
	s = src;
	if (d <= s)
	{
		while (n--)
			*d++ = *s++;
	}
	else if (dest > src)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

/* int main()
{
    char buffer[] = "abcdef";

    ft_memmove(buffer + 2, buffer, 3);
    printf("Using ft_memmove: %s\n", buffer);

    strcpy(buffer, "abcdef");
    memcpy(buffer + 2, buffer, 3);
    printf("Using memcpy: %s\n", buffer);

    strcpy(buffer, "abcdef");
    memmove(buffer + 2, buffer, 3);
    printf("Using memmove: %s\n", buffer);

    return 0;
} */