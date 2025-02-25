/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:15:12 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/07 18:15:23 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function locate the last ocurrence of c 
 * 
 * @param s the whole strings
 * @param c the character that want to find
 */
char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (s[s_len] == (char)c)
			return ((char *)&s[s_len]);
		s_len--;
	}
	return (NULL);
}

/* int main(void)
{
	char	str[] = "Hello Ni Heao";
	char	find = 'o';
	printf("%s", ft_strrchr(str, find));
	return (0); 
} */