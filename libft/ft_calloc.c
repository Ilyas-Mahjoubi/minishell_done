/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:05:46 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/20 17:56:35 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void	fft_bzero(void *str, size_t n)
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb == 0 && size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	str = (char *)malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	fft_bzero(str, nmemb * size);
	return ((void *)str);
}
/*
int main(void)
{
	char	*a = (char *)ft_calloc(5, sizeof(char));
	if (a != NULL)
		free(a);
}
change bzero to test*/
