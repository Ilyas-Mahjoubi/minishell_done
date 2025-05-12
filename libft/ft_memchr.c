/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:02:39 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/20 11:16:41 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sc;
	size_t			i;

	str = (unsigned char *)s;
	sc = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (str[i] == sc)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	const char *s = "abcdefghi";
	printf("%s",(char *)ft_memchr(s, 'b', 10)); 
}*/
