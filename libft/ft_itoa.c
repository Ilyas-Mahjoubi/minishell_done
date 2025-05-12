/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:34:51 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/23 15:34:51 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_counter(int n)
{
	int	count;

	count = 0;
	if (n < 0 || (n == 0))
	{
		if (n == -2147483648)
			return (11);
		if (n < 0)
		{
			count++;
			n = (n * -1);
		}
		if (n == 0)
			count++;
	}
	while (n != 0)
	{
		n = (n / 10);
		count++;
	}
	return (count);
}

static char	*ft_converter(int n, char *str, int len)
{
	if (n == -2147483648)
	{
		str[0] = 45;
		str[1] = 50;
		n = 147483648;
	}
	if (n < 0)
	{
		n = n * -1;
		str[0] = 45;
	}
	str[len] = '\0';
	len--;
	while (n > 9 && len >= 0)
	{
		str[len] = (n % 10) + 48;
		len --;
		n /= 10;
	}
	str[len] = n + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = ft_counter(n);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_converter(n, str, (count));
	return (str);
}
/*
int	main(void)
{
	char    *str;
	str = (char *)ft_itoa(-1234567);
	if (str != NULL)
	{
		printf("%s", str);
		free(str);
	}
}*/
