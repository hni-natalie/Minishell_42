/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:22:13 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/03 16:12:13 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// why (unsigned char)c is needed
// as c take int so need to cast it back to unsigned char 
// the computer know that it takes c as ascii value

/**
 * @brief function writes n bytes of value c (converted to an unsigned char)
 *        to the string *str
 * @param *str - the string 
 * @param c - the letter that want to replace
 * 
 * @return str (the new string)
 */
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) str;
	while (n-- > 0)
		*p++ = (unsigned char)c;
	return (str);
}

// str[] - function are allow to edit
// *str - can't edit only go through

/* int main (void)
{
	char	str1[50] = "Hello Sleep ByeBye";
	char	str2[10] = "hello";
	
	memset(str1 + 6, '*', 5);
	ft_memset(str1 + 6, '*', 5);
	printf("%s\n", str1);
	printf("%s\n", str1);

	ft_memset(str2 + 2, '0', 3);
	memset(str2 + 2, '*', 3 * sizeof(char));
	printf("%s\n", str2);
} */