/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:28:28 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/18 18:53:13 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*dea;

	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	i = 0;
	sr = (unsigned char *)src;
	dea = (unsigned char *)dest;
	while (i < n)
	{
		dea[i] = sr[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "ciaoMUNDO";
	char	dest[9];

	ft_memcpy(dest, src, 9);
	printf("%s", dest);
}*/
