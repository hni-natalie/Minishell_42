/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:27:06 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/20 20:22:07 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	returns length of initial part of str that contains
 * 			only chars from accept
 * 
 * @param s the string to check
 * @param accept the char that to match
 */

size_t	ft_strspn(const char *s, const char *accept)
{
	int		i;
	size_t	count;
	
	if (!s || !accept)
		return (0);
	i = 0;
	count = 0;
	while (*s)
	{
		while (accept[i] && *s != accept[i])
			i++;
		if(accept[i] == '\0')
			return (count);
		i = 0;
		count++;
		s++;
	}
	return (count);
}