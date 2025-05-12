/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:08:10 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/20 15:51:38 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[a] != '\0' && a < len)
	{
		b = 0;
		while (big[a + b] == little[b] && little[b] != '\0' && (a + b) < len)
			b++;
		if (little[b] == '\0')
			return ((char *)&big[a]);
		a++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*big = "Hellowoworlddd";
	char	*little ="";
	printf("%s", ft_strnstr(big, little, 3));
}*/
