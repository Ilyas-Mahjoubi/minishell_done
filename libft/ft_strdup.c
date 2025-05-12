/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:47:47 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/20 21:10:10 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
/*
int	main(void)
{
	char	*s = "helloworld";
	char *dup = (char *)ft_strdup(s);
	printf("%s", dup);
	if (dup != NULL)
		free(dup);
	return (0);
}*/
