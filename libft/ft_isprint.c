/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:09:16 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/03 15:14:26 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function check the specific letter whether is it printable character
 * @param str(int) 
 *  
 * @return 1 if it is letter
 * @return 0 if it is not 
 */
int	ft_isprint(int str)
{
	if (str >= ' ' && str <= '~')
		return (1);
	else
		return (0);
}

// int main (void)
// {
// 	char	str1 = 'H';
// 	char	str2 = '1';
// 	char 	str3 = 0x7F;
// 	char	str4 = -12;

// 	int result1 = ft_isprint(str1);
//     printf("%d\n", result1);
// 	printf("%d\n", isprint(str1));

// 	int result2 = ft_isprint(str2);
//     printf("%d\n", result2);
// 	printf("%d\n", isprint(str2));

// 	int result3 = ft_isprint(str3);
//     printf("%d\n", result3);
// 	printf("%d\n", isprint(str3));

// 	int result4 = ft_isprint(str4);
//     printf("%d\n", result4);
// 	printf("%d\n", isprint(str4));
// }
