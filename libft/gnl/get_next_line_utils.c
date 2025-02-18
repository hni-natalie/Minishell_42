/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:17:47 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 16:26:07 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	int	i;

	i = gnl_ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*ptr;

	len1 = gnl_ft_strlen(s1);
	len2 = gnl_ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < len1)
		ptr[i] = s1[i];
	j = -1;
	while (++j < len2)
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

void	*gnl_ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && count > UINT_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	gnl_ft_bzero(ptr, size * count);
	return (ptr);
}

void	gnl_ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		ptr[n] = 0;
}
