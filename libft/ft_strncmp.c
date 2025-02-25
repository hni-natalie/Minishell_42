/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:07:23 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/27 09:04:25 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function compare not more than n characters 
 * characters that appear aftre a '\0' character are not compared 
 * 
 * @param *s1 first strings
 * @param *s2 second strings 
 * @param n numbers of character to compare
 * 
 * @return integer greater than, equal to, or less than 0
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

/* int main()
{
  char str1[] = "test\0gh00", str2[] = "test\0", str3[] = "abca\0ees";
  int result;

  result = ft_strncmp(str1, str2, 6);
  result = strncmp(str1, str2, 7);
  printf("ft_strcmp(str1, str2) = %d\n", result);
  printf("strcmp(str1, str2) = %d\n", result);

  result = ft_strncmp(str1, str3, 6);
  result = strncmp(str1, str3, 6);
  printf("ft_strcmp(str1, str3) = %d\n", result);
  printf("strcmp(str1, str3) = %d\n", result);

  return 0;
} */