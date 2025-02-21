/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:39:47 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/28 11:46:20 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printfstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*s && ++i)
		write(1, s++, 1);
	return (i);
}

static int	ft_putptr(uintptr_t ptr)
{
	int		len;
	char	*hexa;

	hexa = "0123456789abcdef";
	len = 0;
	if (ptr >= 16)
		len += ft_putptr(ptr / 16);
	len += write(1, &hexa[ptr % 16], 1);
	return (len);
}

int	ft_printfptr(uintptr_t ptr)
{
	int		print_len;

	print_len = 0;
	print_len += write(1, "0x", 2);
	if (ptr == 0)
		print_len += write(1, "0", 1);
	else
		print_len += ft_putptr(ptr);
	return (print_len);
}

int	ft_printfhexa(unsigned int num, const char format)
{
	int		len;
	char	*hexa_l;
	char	*hexa_u;

	hexa_l = "0123456789abcdef";
	hexa_u = "0123456789ABCDEF";
	len = 0;
	if (num >= 16)
	{
		len += ft_printfhexa(num / 16, format);
		len += ft_printfhexa(num % 16, format);
	}
	else
	{
		if (format == 'x')
			len += write(1, &hexa_l[num % 16], 1);
		else if (format == 'X')
			len += write(1, &hexa_u[num % 16], 1);
	}
	return (len);
}

/* int main(void)
{
	int i = -1;
	printf("ft_printfunbr= %u\n", ft_printfunbr(i));
	printf("original= %u\n", i);
	printf("ft_printfnbr= %d\n", ft_printfnbr(i));
	printf("original= %d\n", i);
	printf("ft_printfhexa= %x\n", ft_printfhexa(i, 'x'));
	printf("original= %x\n", i);
	printf("ft_printfhexa= %X\n", ft_printfhexa(i, 'X'));
	printf("original= %X\n", i);
	printf("ft_printf= %p\n", ft_printfptr(-1));
	printf("original= %p\n", -1);
} */