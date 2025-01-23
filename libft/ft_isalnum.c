/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:24:16 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:38:28 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

*/

/**
 * @brief function check the specific letter 
 	whether is it alphabet and digit number
 * @param str(int) 
 *  
 * @return 1 if it is letter
 * @return 0 if it is not 
 */
int	ft_isalnum(int str)
{
	if ((str >= '0' && str <= '9') || (str >= 'A' && str <= 'Z')
		|| (str >= 'a' && str <= 'z'))
		return (1);
	else
		return (0);
}

/* int main(void)
{
	char	str1 = 'H';
	char	str2 = '1';
	char 	str3 = ' ';
	char	str4 = '*';

	int result1 = ft_isalnum(str1);
    printf("%d\n", result1);
	printf("%d\n", isalnum(str1));

    int result2 = ft_isalnum(str2);
    printf("%d\n", result2);
	printf("%d\n", isalnum(str2));

    int result3 = ft_isalnum(str3);
    printf("%d\n", result3);
	printf("%d\n", isalnum(str3));

	int result4 = ft_isalnum(str4);
    printf("%d\n", result4);
	printf("%d\n", isalnum(str4));
} */
