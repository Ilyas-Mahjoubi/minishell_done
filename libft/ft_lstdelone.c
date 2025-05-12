/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:19 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 17:44:59 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode -> content = content;
	newnode -> next = NULL;
	return (newnode);
}
void	del(void *content)
{
	if (content)
		free(content);
} */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst -> content);
		free (lst);
	}
}
/*
  int	main(void)
{
	t_list	*head = ft_lstnew(strdup("Hello"));
	t_list	*mid = ft_lstnew(strdup("Fuck"));
	t_list	*last = ft_lstnew(strdup("World"));
	head -> next = mid;
	mid -> next = last;
	t_list	*temp = head;
	while (temp)
	{
		printf("%s", (char *)temp -> content);
		temp = temp -> next;
	}
	printf("\nafter\n");
	mid -> next = NULL;
	ft_lstdelone(last, del);
	temp = head;
	while (temp)
	{
		printf("%s", (char *)temp -> content);
		temp = temp -> next;
	}
	ft_lstdelone(mid, del);
	ft_lstdelone(head, del);

} */
