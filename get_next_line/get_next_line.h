/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:51:46 by tkurukul          #+#    #+#             */
/*   Updated: 2025/01/27 18:04:23 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>

char		*ft_check_char(char *str, char c);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *str);
char		*get_next_line(int fd);

#endif
