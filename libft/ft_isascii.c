/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:47:29 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/03 15:07:16 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function check the specific letter whether is it ascii value
 * @param str(int) 
 *  
 * @return 1 if it is letter
 * @return 0 if it is not 
 */
int	ft_isascii(int str)
{
	if (str >= 0 && str <= 127)
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	str1 = 'H';
// 	char	str2 = 0x7F;
// 	char 	str3 = ' ';
// 	char	str4 = -12;

// 	int result1 = ft_isascii(str1);
//     printf("%d\n", result1);
// 	printf("%d\n", isascii(str1));

//     int result2 = ft_isascii(str2);
//     printf("%d\n", result2);
// 	printf("%d\n", isascii(str2));

//     int result3 = ft_isascii(str3);
//     printf("%d\n", result3);
// 	printf("%d\n", isascii(str3));

// 	int result4 = ft_isascii(str4);
//     printf("%d\n", result4);
// 	printf("%d\n", isascii(str4));
// }