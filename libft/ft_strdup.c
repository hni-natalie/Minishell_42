/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:02:43 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/08 13:02:44 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Concept:
1. find the length of s and allocate memory of it
2. define a variable that hold the first character
3. go through the string and copy into the memory allocated
4. add null-terminator
5. return the first character
*/

/**
 * @brief function allocate sufficient memory for a copy of the string s
 * 
 * @param *s the strings that wanted to copy
 * 
 * @return returns a pointer to s
 * @return NULL if insufficient memory is available
 */
char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*start;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	start = ptr;
	while (*s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (start);
}

/* int main(void)
{
	char str[] = "Surviving OMG";
	printf("%s\n", strdup(str));
	printf("%s", ft_strdup(str));
	free(ft_strdup(str));
	free(strdup(str));		
} */