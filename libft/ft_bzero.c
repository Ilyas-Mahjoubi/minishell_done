/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:10:52 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/18 18:27:52 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char	str[10] = "tuttoer";
	int	i = 0;
	ft_bzero(str, 5);
	while (i < 5)
	{
		printf("%d", str[i]);
		i++;
	}
	printf("\n%s",str);
}*/
