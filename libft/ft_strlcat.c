/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:23:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/07 12:24:01 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that appends string src to the end of dst 
 * append at most dstsize - strlen(dst) - 1 characters 
 * 
 * @param dst location where src is copied to
 * @param src where characters will be copied from 
 * @param dstsize numbers of characters that will be copied
 * 
 * @return total length of src and dst if dst_size > dstlen
 * @return total length of src and dstsize if dst_size <= dstlen
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* int main() 
{
    char dest[20] = "This is ";
    char src[15] = "World!!!";
	size_t i = 9;

	int result_len = ft_strlcat(dest, src, i);
	int result_len_1 = strlcat(dest, src, i);
    printf("Concatenated string: %s\n", dest);
    printf("Total length after concatenation: %d\n", result_len);
	printf("%d", result_len_1);
    return 0;
} */