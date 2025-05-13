/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:31:10 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/13 18:07:55 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free3(char ***matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free_mat(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_all(t_info *info)
{
	free3(info->exec);
	free_mat(info->env);
	close_fd(info->fd_in_out);
}
