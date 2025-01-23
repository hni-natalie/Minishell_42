/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:19:11 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:49 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function copies up  to dstsize -1 characters 
    from the string src to dst,
 * NUL - terminating the result if dstsize is not 0
 * 
 * @param dst - the location to copy the words 
 * @param src - the location to words copied from 
 * @param dstsize - number of words to copy
 * 
 * @return total length of src
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/* int main() {
    char src1[] = "Hello, world!";
    char dest1[20]; 

    unsigned int length1 = ft_strlcpy(dest1, src1, 20);
    printf("Test Case 1:\n");
    printf("Length of copied string: %u\n", length1);
	printf("%s\n\n", dest1);

    char src2[] = "lorem ipsum dolor sit amet";
    char dest2[20]; 

    unsigned int length2 = ft_strlcpy(dest2, src2, 10);
    printf("Test Case 2:\n");
    printf("Length of copied string: %u\n", length2);
	printf("%s\n\n", dest2);

    char src3[] = "";
    char dest3[5]; 

    unsigned int length3 = ft_strlcpy(dest3, src3, 5);
    printf("Test Case 3:\n");
	printf("%s end\n", dest3);
    printf("Length of copied string: %u\n\n", length3);

    char src4[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char dest4[15]; 

    unsigned int length4 = ft_strlcpy(dest4, src4, 15);
    printf("Test Case 4:\n");
    printf("Length of copied string: %u\n", length4);
	printf("%s\n", dest4);

    return 0;
} */