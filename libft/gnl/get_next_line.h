/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:03:29 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/09 10:05:40 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif 

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*get_line(char *str);
char	*read_line(int fd, char *current);
char	*rest_of_line(char *line);
size_t	gnl_ft_strlen(const char *str);
char	*gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_strjoin(char const *s1, char const *s2);
void	*gnl_ft_calloc(size_t count, size_t size);
void	gnl_ft_bzero(void *s, size_t n);

#endif
