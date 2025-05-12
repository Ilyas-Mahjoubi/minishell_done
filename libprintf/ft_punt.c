/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:03:20 by tkurukul          #+#    #+#             */
/*   Updated: 2025/04/30 22:19:20 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_eri(int fd, unsigned long ptr)
{
	int		i;
	int		resto;
	char	*lower;

	i = 0;
	lower = "0123456789abcdef";
	if (ptr > 15)
	{
		i += ft_eri(fd, ptr / 16);
	}
	resto = ptr % 16;
	i += write (fd, &lower[resto], 1);
	return (i);
}

int	ft_punt(int fd, void *ptr)
{
	int	i;

	if (!ptr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	i = 0;
	i += write(fd, "0x", 2);
	i += ft_eri(fd, (unsigned long)ptr);
	return (i);
}
/* int main(void)
{
	char str[] = "Hello, world!";
	void *ptr1 = str;
	int i = ft_punt(ptr1);
	printf("\n%d", i);
}*/
