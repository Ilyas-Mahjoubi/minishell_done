/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:38:01 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/27 20:38:25 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	ft_strlten(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	b;

	b = 0;
	i = ft_strlten(dest);
	while (src[b] != '\0')
	{
		dest[i] = src[b];
		b++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	total;

	total = ft_strlten(s1) + ft_strlten(s2);
	str = (char *)malloc((total + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_strcat(str, (char *) s1);
	ft_strcat(str, (char *) s2);
	return (str);
}
/*
int main(void)
{
	char	*s1 = "Tuamadre";
	char	*s2 = "pottono";
	char	*str = (char *)ft_strjoin(s1, s2);
	if (str != NULL)
	{
		printf("%s", str);
		free(str);
	}
	return (0);
}
*/
