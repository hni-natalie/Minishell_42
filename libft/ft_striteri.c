/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:06:18 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:35:55 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_striteri doesn't return anything and 
// works directly on the original string
// It can only use char array in the main body
// However, it can't use pointer as pointer point to 
// the particular memory address
// ft_striteri change the original string and so change the memory address

/**
 * @brief function that apply a function to each character of a string
 * each character is transmitted by address to 'f' so 
 	it can be modified if necessary
 * 
 * @param *s string over to interate
 * @param f void function to apply each character
 * 
 * @return a new string resulting of the successive application of 'f'
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* void	uppercase(unsigned int i, char *c)
{
	if(i % 2 == 0)
		*c = toupper(*c);
	else
		*c = tolower(*c);
}

int main(void)
{
	char str[] = "hello this is Natalie";
	ft_striteri(str, uppercase);
	printf("%s", str);
} */