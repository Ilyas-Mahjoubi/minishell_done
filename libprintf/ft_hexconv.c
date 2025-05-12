/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:14:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/30 22:19:14 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexconv(int fd, int unsigned nb, const char c)
{
	int		i;
	int		resto;
	char	*upp;
	char	*lower;

	upp = "0123456789ABCDEF";
	lower = "0123456789abcdef";
	i = 0;
	if (nb > 15)
	{
		i += ft_hexconv(fd, nb / 16, c);
	}
	resto = nb % 16;
	if (c == 'x')
		i += write (fd, &lower[resto], 1);
	if (c == 'X')
		i += write(fd, &upp[resto], 1);
	return (i);
}
/* int	main(void)
{
	ft_hexconv(-42, 'X');
} */
