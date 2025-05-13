/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:55:28 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/13 18:04:24 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_refresh_fd(t_info *info)
{
	dup2(info->fd_in_out[0], STDIN_FILENO);
	dup2(info->fd_in_out[1], STDOUT_FILENO);
	close(info->fd_in_out[0]);
	close(info->fd_in_out[1]);
}
