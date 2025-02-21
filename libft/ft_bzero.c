/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:41:24 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 12:35:56 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
1. Remember to assign void pointer to unsigned char pointer 
2. Going through the n, change the character to zero(NULL)
*/

/**
 * @brief function writes n zeroed bytes to the string s
 * @param *s - can be char or int 
 * @param n - num of letter that want to change to zero
 * 
 * @return none as it is a void function
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	if (n)
		while (n-- > 0)
			p[n] = 0;
}

/* it's better to use arr to test 
printf see \0 will end straight away 
he won't print the rest of the word behind */

/* int main(void)
{
	char	buffer[9];

	for (size_t i = 0; i < sizeof(buffer); i++)
		buffer[i] = 0x7f;

	for (size_t i = 0; i < sizeof(buffer); i++)
		printf("%d ", buffer[i]);
	printf("\n");
	ft_bzero(buffer, sizeof(buffer));
	for (size_t i = 0; i < sizeof(buffer); i++)
		printf("%d ", buffer[i]);
	printf("\n");
	return (0);
} */
