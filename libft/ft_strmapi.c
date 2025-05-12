/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:13:28 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/25 00:13:28 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*static char	ft_f(unsigned int i, char c)
{
	c -= 32;
	c += i;
	return (c);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = (char)f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int     main(void)
{
    char    *src = "abcd";
    char    *str =(char *)ft_strmapi(src, ft_f);
    if (str != NULL)
    {
        printf("%s", str);
        free(str);
    }
}*/
