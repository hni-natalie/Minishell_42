/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:17:54 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/15 16:56:29 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function check the specific letter whether is it digit number
 * @param str(int) 
 *  
 * @return 1 if it is letter
 * @return 0 if it is not 
 */
int	ft_isdigit(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

/* int main(void)
{
	char	str1 = 'H';
	char	str2 = '1';
	char 	str3 = ' ';
	char	str4 = '*';

	int result1 = ft_isdigit(str1);
    printf("%d\n", result1);
	printf("%d\n", isdigit(str1));

	int result2 = ft_isdigit(str2);
    printf("%d\n", result2);
	printf("%d\n", isdigit(str2));

	int result3 = ft_isdigit(str3);
    printf("%d\n", result3);
	printf("%d\n", isdigit(str3));

	int result4 = ft_isdigit(str4);
    printf("%d\n", result4);
	printf("%d\n", isdigit(str4));
} */
