/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:44:32 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/07/04 17:45:19 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

int		ft_printf(const char *fmt, ...);

int		ft_printfchar(int c);
int		ft_printfstr(char *s);
int		ft_printfnbr(int num);
int		ft_printfunbr(unsigned int num);
int		ft_printfhexa(unsigned int num, const char format);
int		ft_printfptr(uintptr_t ptr);

#endif
