/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:49:03 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:05 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function converts a lower-case letter to 
 	corresponding upper-case letter
 * 
 * @param c representable as an unsigned char or the value of EOF
 * 
 * @return corresponding upper-case letter if there is one; 
 * @return otherwise, unchanged 
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

// int main()
// {
//     char c;

//     c = 'm';
//     printf("%c -> %c", c, ft_toupper(c));

//     c = 'd';
//     printf("\n%c -> %c", c, ft_toupper(c));

//     c = '4';
//     printf("\n%c -> %c", c, ft_toupper(c));
//     return 0;
// }