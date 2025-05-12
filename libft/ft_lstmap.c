/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:44:54 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:46:24 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	del(void *content)
{
	if (content != NULL)
		free(content);
} */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	void	*loopcont;
	t_list	*newlist;

	newlist = NULL;
	while (lst)
	{
		loopcont = f(lst -> content);
		newnode = ft_lstnew(loopcont);
		if (newnode == NULL)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst -> next;
	}
	return (newlist);
}

/* void	*f(void *content)
{
	int i = 0;
	char *str = (char *)content;
	char	*newstr = strdup(str);
	while (newstr[i])
	{
		newstr[i] = toupper(newstr[i]);
		i++;
	}
	return (newstr);
} */

/* int	main(void)
{
	t_list	*head = ft_lstnew(ft_strdup("The"));
	t_list	*mid = ft_lstnew(ft_strdup("Fucking"));
	t_list	*last = ft_lstnew(ft_strdup("PC"));
	t_list	*temp = head;
	head -> next = mid;
	mid -> next = last;
	t_list	*new = ft_lstmap(head, f, del);
	while (temp)
	{
		printf("%s ", (char *)temp -> content);
		temp = temp -> next;
	}
	printf("\n after new alloc \n");
	temp = new;
	while (temp)
	{
		printf("%s ", (char *) temp -> content);
		temp = temp -> next;
	}
} */
