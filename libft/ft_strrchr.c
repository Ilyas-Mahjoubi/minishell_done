/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:03:09 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/26 16:47:39 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	a;

	a = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if ((unsigned char)s[i] == a)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
/*
int main(void)
{
	char *s = "abcdefghij";
	printf("%s", ft_strrchr(s, 'a'));
}*/
