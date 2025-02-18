/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:48 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 11:58:57 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Concept of writing ft_atoi
1. Skip the whitespace
2. If there is a + sign and followed by number behind it, then continue 
3. If there is a - sign and followed by number behind it, 
	then add negative and continue
4. If is it a number, then apply the formula below
   sum = sum * 10 + (str - '0')
5. return sum * neg
*/

/**
 * @brief function that convert int in strings to integer
 * 
 * @param str int in strings
 * 
 * @return integer
 */
int	ft_atoi(const char *str)
{
	int	sum;
	int	neg;

	sum = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' && (*(str + 1) >= '0' && *(str + 1) <= '9'))
		str++;
	if (*str == '-' && (*(str + 1) >= '0' && *(str + 1) <= '9'))
	{
		neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return (sum * neg);
}

// int main(void)
// {
// 	int val;
// 	int ft_val;
// 	char str[] = "    -557gdfg76";
// 	val = atoi(str);
// 	ft_val = ft_atoi(str);
// 	printf("%d\n", val);
// 	printf("%d", ft_val);
// 	return (0);
// }