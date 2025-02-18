/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:26:21 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:15 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fd - file descriptor acts as a handle that allows the process
// to access and manipulate te file 
// standard input (stdin) : file descriptor 0
// standard ouput (stdout) : file descriptor 1
// standard error (stderr) : file descriptor 2

/**
 * @brief function that write character c on a specified file descriptor fd
 * 
 * @param c character to write
 * @param fd file descriptor on which to write 
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int main(void)
{
	char c = 'a';
	int fd1 = 1;
	int fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// O_WRONGLY = opened in write-only mode
	// O_CREAT = does not exist, it will be created
	// O_TRUNC = already exists, its content will be truncated 0 bytes
	// 0644: Set the file permission to rw-r--r-- 
	// (read and write for the owner, and read-only for the group and others)
	
	if (fd2 == -1)
	// if fd2 fails to open it will return -1 
	{
		perror("open"); 
		// a function that is used to print an error message 
		// corresponding to the current value of the global variable 
		return 1;
		// indicate an error occurred and exits
	}
	ft_putchar_fd(c, fd1);
	ft_putchar_fd(c, fd2);
	close(fd2);
	return 0;
}
 */