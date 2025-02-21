/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:28 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/12 10:45:44 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that concatenate 2 strings in a new string
 * 
 * @param s1 prefix string
 * @param s2 sufffix string
 * 
 * @return the new string
 */
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < len1)
		ptr[i] = s1[i];
	j = -1;
	while (++j < len2)
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	free(s1);
	return (ptr);
}

/* int main(void)
{
    char str1[] = "Hello ";
    char str2[] = "I'm Natalie";
    printf("%s", ft_strjoin(str1, str2));
	free(ft_strjoin(str1, str2));
} */