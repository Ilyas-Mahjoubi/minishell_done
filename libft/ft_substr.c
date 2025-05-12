/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:03:05 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/26 20:54:39 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ftt_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_stsrdup(const char *s)
{
	int		i;
	int		a;
	char	*str;

	i = 0;
	a = 0;
	while (s[a] != '\0')
		a++;
	str = (char *)malloc((a + 1) * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (&str[0]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	end;
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	end = ftt_strlen((char *)s);
	if (start >= end)
		return (ft_stsrdup(""));
	i = 0;
	if (len > end - start)
		len = end - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*s = "Hellohelloworldhellohello";
	char	*str =(char *)ft_substr(s, 10, 1);
	if (str != NULL)
	{
		printf("%s", str);
		free(str);
	}
	return (0);
}*/
