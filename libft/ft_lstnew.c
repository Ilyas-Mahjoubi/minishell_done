/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:45:39 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/28 23:46:50 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
// int	main(void)
// {
// 	char *content = "Test";
// 	t_list	*node = ft_lstnew((void *)content);
// 	if(node)
// 	{
// 		printf("%s", (char *)node -> content);
// 		printf("%p", (void *)node -> next);
// 	}
// }
