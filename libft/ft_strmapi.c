/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:18:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/10 13:18:12 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that apply a function to each character of a string
 * 
 * @param *s string over to interate
 * @param f function to apply each character
 * 
 * @return a new string resulting of the successive application of 'f'
*/
char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* char	uppercase(unsigned int i, char c)
{
	if(i % 2 == 0)
		return toupper(c);
	else
		return tolower(c);
}

int main(void)
{
	char *ptr = ft_strmapi("Hello, Hi, Bye", uppercase);
	printf("%s", ptr);
} */