/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:03:14 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:46:34 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}
/*
t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode -> content = content;
	newnode -> next = NULL;
	return (newnode);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;

}

int	main(void)
{
	t_list	*head = ft_lstnew("World");
	t_list	*newn = ft_lstnew("Fucking");
	ft_lstadd_front(&head, newn);
	t_list	*n = ft_lstnew("Hello");
	ft_lstadd_front(&head, n);
	t_list	*last_node = ft_lstlast(head);
	printf("%s", (char *)last_node->content);
}*/
