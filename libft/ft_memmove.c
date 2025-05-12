/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:29:42 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/26 16:46:51 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*des;
	unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	else if (!n)
		return (dest);
	des = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (des > sr)
	{
		while (n--)
			des[n] = sr[n];
	}
	else if (des < sr)
	{
		ft_memcpy(des, sr, n);
	}
	return (dest);
}
/*
#include <string.h>
int	main(void)
{
	char	src[20] = "Hello World";
	char	*dest = src + 3;
	memmove(dest, src, 5);
	printf("%s", dest);
}*/
