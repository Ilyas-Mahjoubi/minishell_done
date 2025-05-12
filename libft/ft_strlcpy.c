/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:47:05 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/18 18:10:20 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	while (a < (size - 1) && src[a])
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = '\0';
	return (i);
}
/*
int	main(void)
{
	char	*src = "ciao";
	char dest[2];
	ft_strlcpy(dest, src, 2);

	printf("%s", dest);
	printf("\n%zu", ft_strlcpy(dest, src, 2));
}
 -size > 0
-size = dest size with null byte;
-add null byte
-copy*/
