/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:31:08 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:26 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim(const char *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*new_str(const char *str, size_t start, size_t len)
{
	char	*ptr;
	char	*new;

	if (start >= ft_strlen(str) || len <= 0 || ft_strlen(str) == 0)
		return (ft_strdup(""));
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	new = ptr;
	while (len--)
		*ptr++ = str[start++];
	*ptr = '\0';
	return (new);
}

/**
 * @brief function that trim character set from string
 * 
 * @param s string to trim 
 * @param set characters to trim 
 * 
 * @return a trimmed copy of s1
 */
char	*ft_strtrim(char const *s, char const *set)
{
	int	i;
	int	j;

	if (!s || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while (trim(set, s[i]))
		i++;
	while (trim(set, s[j]))
		j--;
	return (new_str(s, i, j - i + 1));
}

/* int main(void)
{
	char str[] = "abcdedaba";
	char trim[] = "acb";
	char *ptr = ft_strtrim(str, trim);
	printf("%s", ptr);
	free(ptr);
} */