/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:48:51 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/06/11 14:49:15 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that write an int on a specified file descriptor
 * 
 * @param n int to write
 * @param fd file descriptor on which to write
*/
void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	nbr;

	num = n;
	if (num < 0)
	{
		num = -num;
		write(fd, "-", 1);
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	nbr = (num % 10) + '0';
	write(fd, &nbr, 1);
}

/* int main(void)
{
	int num = -2147483648;
	int fd1 = 1;
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
	ft_putnbr_fd(num, fd1);
	ft_putnbr_fd(num, fd2);
	close(fd2);
	return 0;
} */
