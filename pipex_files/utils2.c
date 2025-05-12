/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:37:59 by tkurukul          #+#    #+#             */
/*   Updated: 2025/03/01 16:41:42 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	failure(int fd[2], char *str)
{
	close_fd(fd);
	perror(str);
	return (-1);
}

void	close_fd(int *ar)
{
	if (ar[0] >= 0)
		close(ar[0]);
	if (ar[1] >= 0)
		close(ar[1]);
}

void	wait_for_process(int pid1, int pid2)
{
	int		status;

	if (pid1 > 0 && pid2 > 0)
	{
		if (waitpid(pid1, &status, 0) == -1
			|| waitpid(pid2, &status, 0) == -1)
		{
			perror("FAILED TO WAIT");
			exit(1);
		}
	}
}

void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (free(matrix));
	while (matrix[i] != NULL)
		i++;
	if (matrix[i] == NULL)
		i--;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
	return ;
}
