/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:39:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:04 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that write a string on a specified 
 	file descriptor and follow by a newline
 * 
 * @param *s string to write 
 * @param fd file descriptor on which to write
*/
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

/* int main(void)
{
	char c[] = "Hello How are you  bYe !";
	int fd1 = STDOUT_FILENO;
	int fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// O_WRONGLY = opened in write-only mode
	// O_CREAT = does not exist, it will be created
	// O_TRUNC = already exists, its content will be truncated 0 bytes
	if (fd2 == -1)
	// if fd2 fails to open it will return -1 
	{
		perror("open"); 
		// a function that is used to print an error message 
		// corresponding to the current value of the global variable 
		return 1;
	}
	ft_putendl_fd(c, fd1);
	ft_putendl_fd(c, fd2);
	close(fd2);
	return 0;
} */