/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:00:06 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:33:59 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function converts a upper-case letter 
 	to corresponding lower-case letter
 * 
 * @param c representable as an unsigned char or the value of EOF
 * 
 * @return corresponding lower-case letter if there is one; 
 * @return otherwise, unchanged 
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

// int main()
// {
//     char c;

//     c = 'M';
//     printf("%c -> %c", c, ft_tolower(c));

//     c = 'D';
//     printf("\n%c -> %c", c, ft_tolower(c));

//     c = '4';
//     printf("\n%c -> %c", c, ft_tolower(c));
//     return 0;
// }
