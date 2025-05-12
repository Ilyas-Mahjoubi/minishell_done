/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:12:21 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/20 10:31:58 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (((unsigned char )s1[i]) - ((unsigned char )s2[i]));
		}
		i++;
	}
	if (i < n)
		return ((unsigned char )s1[i] - (unsigned char )s2[i]);
	return (0);
}
/*
int main(void)
{
	char 	*s1 = "ciao";
	char	*s2 = "ciaoa";
	printf("%d", ft_strncmp(s1, s2, 4));
}*/
