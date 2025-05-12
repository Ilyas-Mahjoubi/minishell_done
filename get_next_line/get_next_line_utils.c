/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:21:36 by tkurukul          #+#    #+#             */
/*   Updated: 2025/01/08 14:57:31 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	int				i;
	int				j;
	unsigned int	total;

	i = 0;
	j = 0;
	total = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((total + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

char	*ft_strdup(const char *s)
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
