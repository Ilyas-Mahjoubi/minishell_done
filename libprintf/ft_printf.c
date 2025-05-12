/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:07:57 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/08 12:33:46 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check(int fd, const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == '%')
		count += ft_putcharr(fd, '%');
	else if (c == 'c')
		count += ft_putcharr(fd, va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(fd, va_arg(args, char *));
	else if (c == 'p')
		count += ft_punt(fd, va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(fd, va_arg(args, int));
	else if (c == 'u')
		count += ft_unputnbr(fd, va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_hexconv(fd, va_arg(args, unsigned int), c);
	return (count);
}


int	ft_printf(int fd,const char *convs, ...)
{
	va_list		args;
	int			i;
	int			count;

	count = 0;
	i = 0;
	va_start(args, convs);
	while (convs[i] != '\0')
	{
		if (convs[i] == '%' && convs[i + 1])
		{
			i++;
			if (convs[i] == 32)
				return (0);
			count += ft_check(fd, convs[i], args);
		}
		else
			count += ft_putcharr(fd, convs[i]);
		i++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	char *b = "weq";
	char *f = b;
	int i = 123;
	ft_printf("%s Is it? %p", "Is this working? ", f);
} */
