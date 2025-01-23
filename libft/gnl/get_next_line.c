/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:08 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/20 19:12:18 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *current)
{
	char	*line;
	char	*tmp;
	ssize_t	read_check;

	read_check = INT_MAX;
	line = malloc(BUFFER_SIZE + 1 * sizeof(char));
	while (read_check > 0 && !gnl_ft_strchr(current, '\n'))
	{
		read_check = read(fd, line, BUFFER_SIZE);
		if (read_check == -1)
			return (free(line), NULL);
		line[read_check] = '\0';
		tmp = current;
		current = gnl_ft_strjoin(current, line);
		free(tmp);
	}
	free(line);
	return (current);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = gnl_ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rest_of_line(char *line)
{
	int		i;
	int		j;
	char	*remainder;

	if (!line || !(line + 1))
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (!line[i] || !line[i + 1])
		return (free(line), NULL);
	remainder = malloc((gnl_ft_strlen(line) - i) * sizeof(char));
	i++;
	j = 0;
	while (line[i])
		remainder[j++] = line[i++];
	remainder[j] = '\0';
	free(line);
	return (remainder);
}

/**
 * @brief function that return a line read from a file descriptor
 * 
 * @param fd the file descriptor to read from 
 * 
 * @return read line: correct behavior;
 * @return NULL: there is nothing else to read, or error occured
 */
char	*get_next_line(int fd)
{
	static char	*current;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	current = read_line(fd, current);
	buffer = get_line(current);
	current = rest_of_line(current);
	return (buffer);
}

// int main(void)
// {
// 	char *line;
// 	char *line1;
// 	int fd = open("test.txt", O_RDONLY);
// 	int fd1 = open("test1.txt", O_RDONLY);
// 	printf("File Descriptor: %d\n", fd);
// 	printf("Buffer size: %d\n", BUFFER_SIZE);
// 	printf("File Descriptor: %d\n", fd1);
// 	for (int i = 0; i < 2; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("Read: %s\n", line);
// 		if (line)
// 			free(line);
// 	}
// 	for (int j = 0; j < 2; j++)
// 	{
// 		line1 = get_next_line(fd1);
// 		printf("Read second file: %s\n", line1);
// 		free(line1);
// 	}
// 	close(fd);
// 	return (0);
// }
