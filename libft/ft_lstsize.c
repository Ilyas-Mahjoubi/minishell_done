/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:39:56 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 19:43:16 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
/* t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
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
	t_list	*head = ft_lstnew("1");
	t_list	*newnode = ft_lstnew("2");
	ft_lstadd_front(&head, newnode);
	t_list	*anothernode = ft_lstnew("3");
	ft_lstadd_front(&head, anothernode);
	printf("%d", ft_lstsize(head));
} */
