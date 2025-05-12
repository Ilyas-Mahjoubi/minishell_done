/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:41:50 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/27 20:37:32 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static size_t	ft_strlfen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	f;
	size_t	h;

	i = ft_strlfen(dst);
	f = 0;
	h = ft_strlfen(src);
	if (size <= i)
		return (size + h);
	while (((i + f) < size - 1) && src[f] != '\0')
	{
		dst[i + f] = src[f];
		f++;
	}
	dst[i + f] = '\0';
	return (i + h);
}
/*
int	main(void)
{
	char *src = "llo";
	char dst[12] = "He";
	ft_strlcat(dst, src, 5);
	printf("%s", dst);
}

-concat
-size > 0
-return size if dont find null, and dest not null terminated
-return len of dest + len of src if finds null
-size contains null byte */
