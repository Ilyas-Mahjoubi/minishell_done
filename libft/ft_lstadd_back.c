/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:08:05 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:47:08 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
	{
		temp = temp -> next;
	}
	temp -> next = new;
}
/* void	ft_ff(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
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
int	main(void)
{
	t_list	*head = ft_lstnew("World");
	t_list	*newn = ft_lstnew("Fucking");
	ft_ff(&head, newn);
	t_list	*n = ft_lstnew("Hello");
	ft_ff(&head, n);
	t_list	*last = ft_lstnew("!g");
	ft_lstadd_back(&head, last);
	while (head)
	{
		printf("%s", (char *) head -> content);
		head = head -> next;
	}
} */
