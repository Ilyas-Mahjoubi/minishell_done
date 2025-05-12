/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:02:26 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/30 22:15:09 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdarg.h>

int	ft_hexconv(int fd, int unsigned nb, const char c);
int	ft_punt(int fd, void *ptr);
int	ft_putcharr(int fd, char c);
int	ft_putnbr(int fd, int nb);
int	ft_putstr(int fd, char *str);
int	ft_unputnbr(int fd, unsigned int nb);
int	ft_printf(int fd, const char *convs, ...);

#endif
