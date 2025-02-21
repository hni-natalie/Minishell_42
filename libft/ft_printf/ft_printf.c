/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:06:29 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/11/28 11:50:13 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printfchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printfnbr(int n)
{
	int		num_len;
	long	num;

	num_len = 0;
	if (n == 0)
	{
		num_len += write(1, "0", 1);
		return (num_len);
	}
	num = n;
	if (num < 0)
	{
		num_len += write(1, "-", 1);
		num *= -1;
	}
	if (num >= 10)
		num_len += ft_printfnbr(num / 10);
	num_len += ft_printfchar((num % 10) + '0');
	return (num_len);
}

int	ft_printfunbr(unsigned int num)
{
	int	print_len;

	print_len = 0;
	if (num == 0)
	{
		print_len += write(1, "0", 1);
		return (print_len);
	}
	if (num >= 10)
		print_len += ft_printfunbr(num / 10);
	print_len += ft_printfchar((num % 10) + '0');
	return (print_len);
}

static int	ft_type(va_list args, const char format)
{
	int	output;

	output = 0;
	if (format == 'c')
		output += ft_printfchar(va_arg(args, int));
	else if (format == 's')
		output += ft_printfstr(va_arg(args, char *));
	else if (format == 'p')
		output += ft_printfptr(va_arg(args, uintptr_t));
	else if (format == 'd' || format == 'i')
		output += ft_printfnbr(va_arg(args, int));
	else if (format == 'u')
		output += ft_printfunbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		output += ft_printfhexa(va_arg(args, unsigned int), format);
	else if (format == '%')
		output += ft_printfchar('%');
	return (output);
}

// why do printf function returns a value of type int?
// it is to check for errors 
// checking the return value of printf allows us to detext failure 
// early so that won't waste time attempting to write millions of lines
// when the first line already failed

/**
 * @brief a variadic function that outputs formatted 
 * text to the standard output
 * 
 * @param *fmt pointer to the first text string
 * @param ... variables defined
 * 
 * @return the number of characters printed 
*/
int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		output;

	output = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			output += ft_type(args, *fmt);
		}
		else
			output += ft_printfchar(*fmt);
		fmt++;
	}
	va_end(args);
	return (output);
}

/* int main()
{
	int i = 14;
	
	ft_printf("%d\n", i);
	ft_printf("%X\n", i);
	ft_printf("%x\n", i);	
} */
