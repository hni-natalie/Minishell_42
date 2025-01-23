/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:23:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 12:25:36 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	temp;

	count = 0;
	temp = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s != c && temp == 0)
		{
			temp = 1;
			count++;
		}
		else if (*s == c)
			temp = 0;
		s++;
	}
	return (count);
}

const char	*get_next_word(const char *s, char c, char **word)
{
	size_t	word_len;

	while (*s && *s == c)
		s++;
	if (!*s)
		return (NULL);
	if (ft_strchr(s, c))
		word_len = ft_strchr(s, c) - s;
	else
		word_len = ft_strlen(s);
	*word = ft_substr(s, 0, word_len);
	return (s + word_len);
}

/**
 * @brief function that split a string into an array of words
 * 
 * @param s string to split
 * @param c delimiter character
 * 
 * @return an array of strings resulting from the splitting of s
 */
char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		i;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!strings)
		return (NULL);
	while (*s)
	{
		s = get_next_word(s, c, &word);
		if (!s)
			break ;
		strings[i++] = word;
	}
	strings[i] = 0;
	return (strings);
}

/* int main(void)
{
	char str[] = "   45 6 7 -45 5  ";
	char s = ' ';
	char **ptr = ft_split(str, s);
	printf("%d\n", word_count(str, s));
	for (int i = 0; i <= 6; i++)
		printf("%s\n", ptr[i]);
	free(ptr);
} */

// sizeof(char *) calculates the size of a pointer to 'char'
// This is necessary for us to allocate memory for an array of pointer to char *

// when the first array reach the NULL, free the memory to avoid memory leak
// within the loop, it frees the memory allocated for each string in the array 
// after all strings have been freed, it frees the memory 
// allocated for the array itself using free(strings)
// j won't have to return back to 0 
// because u always need to free the previous words

// free(strings[index--]) frees the memory 
// allocated for each string in the array
// after freeing all the individual strings, 
// free(strings) is called to deallocate
// the memory allocated for the array itself