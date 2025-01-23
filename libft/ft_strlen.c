/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:05 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/09 10:03:35 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// why we should use size_t is preferable over int
// size_t ensures that the function can handle very large strings 
// size_t a 64-bit unsigned integer
// while int is usually a 32-bit signed integer

/**
 * @brief function count the letter in the strings
 * @param *str 
 *  
 * @return total length of the strings
 */
size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

// int main()
// {
//     char message[] = "Hello  haha,./";
//     int length = ft_strlen(message);
//     printf("%d\n", length);
// 	printf("%zu", strlen(message));
//     return 0;
// }
