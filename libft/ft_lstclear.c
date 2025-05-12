/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:51:58 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 19:53:40 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  void	del(void *content)
{
	if (content != NULL)
		free(content);
} */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*pointer;

	if (lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (temp)
	{
		pointer = temp -> next;
		del(temp -> content);
		free(temp);
		temp = pointer;
	}
	*lst = NULL;
}
/*  int	main(void)
{
	t_list	*head = ft_lstnew(ft_strdup("The"));
	t_list	*mid = ft_lstnew(ft_strdup("Fucking"));
	t_list	*last = ft_lstnew(ft_strdup("PC"));
	t_list	*temp = head;
	head -> next = mid;
	mid -> next = last;
	while (temp)
	{
		printf("%s", (char *)temp -> content);
		temp = temp -> next;
	}
	printf("\n");
	ft_lstclear(&head, del);
	if (head == NULL)
	printf("NULLBYTE");
}  */
