/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:56:32 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:45:42 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}
/* void	f(void *content)
{
	char *str = (char *)content;
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}

int	main(void)
{
	t_list	*head = ft_lstnew(strdup("Hello"));
	t_list	*node = ft_lstnew(strdup("World"));
	head -> next = node;
	ft_lstiter(head, f);
	while (head)
	{
		printf("%s", (char *)head -> content);
		head = head -> next;
	}
} */
