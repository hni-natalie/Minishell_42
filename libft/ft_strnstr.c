/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:23:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:35 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function search a word from a string
 * characters that appears after a '\0' character are not searched
 * 
 * @param *haystack the strings
 * @param *needle the substring to find
 * @param n number of character to find
 * 
 * @return NULL if substring is not found;
 * @return a pointer to the first character of the 
 	first occurence of needle is returned  
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	if (n == 0)
		return (NULL);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < n && needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

/* int main(void)
{
	const char	str[] = "Goo Hoo Joo Poo";
	const char find[] = " Joo";
	printf("%s\n", strnstr(str, find, sizeof(str)));
	printf("%s", ft_strnstr(str, find, sizeof(str)));
} */