/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:25:34 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/09 17:25:37 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that convert an int to a string
 * 
 * @param n int to be converted
 * 
 * @return the string representing n
*/
static int	ft_intlen(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;
	long	temp_n;
	int		i;

	temp_n = n;
	len = ft_intlen(temp_n);
	i = len - 1;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (temp_n < 0)
	{
		ptr[0] = '-';
		temp_n *= -1;
	}
	if (temp_n == 0)
		ptr[i] = temp_n + '0';
	while (temp_n != 0)
	{
		ptr[i--] = ((temp_n % 10) + '0');
		temp_n = temp_n / 10;
	}
	ptr[len] = '\0';
	return (ptr);
}

/* int main (void)
{
	int n = 2147483647;
	char *ptr = ft_itoa(n);
	printf("%d\n", ft_intlen(n));
	printf("%s", ptr);
	free(ptr);
} */