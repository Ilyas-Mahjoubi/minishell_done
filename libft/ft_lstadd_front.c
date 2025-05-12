/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:51:12 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:46:10 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new -> next = *lst;
	*lst = new;
}
/* void	print_list(t_list *head)
{
	while (head)
	{
		printf("%s", (char *) head -> content);
		head = head -> next;
	}
}
t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
		return(NULL);
	newnode -> content = content;
	newnode -> next = NULL;
	return (newnode);
}
int		main(void)
{
	t_list	*head = ft_lstnew("ME Now!");
	print_list(head);
	printf("\n");
	t_list	*newnode = ft_lstnew("Stop ");
	ft_lstadd_front(&head, newnode);
	print_list(head);
	printf("\n");
	t_list	*node = ft_lstnew("Don't");
	ft_lstadd_front(&head, node);
	print_list(head);
	return (0);
} */
