/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:44:45 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/26 16:45:36 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;

	a = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == a)
			return ((char *)s);
		s++;
	}
	if (a == '\0')
		return ((char *)s);
	return (0);
}
/*
int main(void)
{
	char *s = "Findme";
	printf("%s", ft_strchr(s, '\0'));
}*/
