/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:36:36 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/09 22:46:25 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

t_token *ft_newnode(char *content, t_token_type type)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->content = content; // Assume content is already duplicated if needed
    node->type = type;
    node->next = NULL;
    return (node);
}

void ft_listadd_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	b;

	b = 0;
	while (b < n && src[b] != '\0')
	{
		dest[b] = src[b];
		b++;
	}
	while (b < n)
	{
		dest[b] = '\0';
		b++;
	}
	return (dest);
}

void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
		i++;
	i--;
	while (i >= 0 && matrix[i])
	{
		free(matrix[i]);
		i--;
	}
    free(matrix);
	matrix = NULL;
	return ;
}

