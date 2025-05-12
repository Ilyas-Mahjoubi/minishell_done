/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:38:49 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/25 00:38:49 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*static void	ft_f(unsigned int i, char *c)
{
	*c = *c - 32;
	*c = *c + i;
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

/* int     main(void)
{
    char    src[] = "abcd";
    ft_striteri(src, ft_f);
        printf("%s", src);
} */
