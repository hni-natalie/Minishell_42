/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:06:05 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:38:19 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Why put int str as prototype instead of char str ?
Standard 'ctype' functions can take 'EOF' as an argument 
which is '-1' and is outside the range of 'unsigned char'
'-1' represents the end of the string
using an 'int' arugment allows these functions to handle but 'char' won't
all of the ft_is.. function used for checking 
 */

/**
 * @brief function check the specific letter is it alphabet
 * @param str(int) 
 *  
 * @return 1 if it is letter
 * @return 0 if it is not 
 */
int	ft_isalpha(int str)
{
	if ((str >= 'A' && str <= 'Z') || (str >= 'a' && str <= 'z'))
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
	
	int result1 = ft_isalpha(str1);
    printf("%d\n", result1);
	printf("%d\n", isalpha(str1));

    int result2 = ft_isalpha(str2);
    printf("%d\n", result2);
	printf("%d\n", isalpha(str2));

    int result3 = ft_isalpha(str3);
    printf("%d\n", result3);
	printf("%d\n", isalpha(str3));

	int result4 = ft_isalpha(str4);
    printf("%d\n", result4);
	printf("%d\n", isalpha(str4));
} */