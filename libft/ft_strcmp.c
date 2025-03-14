/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:06:52 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/14 16:50:09 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while ((s1[++i] != '\0' || s2[i] != '\0'))
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}
