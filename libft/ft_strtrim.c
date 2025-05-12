/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:57:40 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/26 16:46:18 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_checkchar(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*ft_strcpy(char *dest, const char *src, int start, int end)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (i < end)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (s1[end] != '\0')
		end++;
	while (s1[start] != '\0' && ft_checkchar(s1[start], set))
		start++;
	while (end > start && ft_checkchar(s1[end - 1], set))
		end--;
	str = (char *)malloc(((end - start) + 1) * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1, start, end);
	return (str);
}
/*
int	main(void)
{
	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !";
 	char *s2 = "Hello \t  Please\n Trim me !";
 	char *ret = ft_strtrim(s1, " \n\t");

	if (ret != NULL)
	{
		printf("%s\n", s1);
		printf("%s\n", ret);
		printf("%s", s2);
		free(ret);
	}
}*/
