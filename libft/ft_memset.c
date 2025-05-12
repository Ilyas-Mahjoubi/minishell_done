/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:17:23 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/18 17:45:32 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *str, int a, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		s[i] = (unsigned char)a;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	str[10];
	ft_memset(str, -45, 5);
	printf("%s",str);
}*/
