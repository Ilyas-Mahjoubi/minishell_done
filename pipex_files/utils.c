/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:04:20 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/05 01:28:39 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**matrix_creation(char *str)
{
	char	**matrix;

	matrix = ft_split(str, 32);
	if (!matrix)
		return (NULL);
	return (matrix);
}

void	in_out_1(int pipefd[2], int fd)
{
	if (dup2(fd, 0) == -1 || dup2(pipefd[1], 1) == -1)
	{
		perror("FAILED DUP2 1");
		exit(1);
	}
	close(fd);
	close(pipefd[1]);
}

void	in_out_2(int pipefd[2], int fd)
{
	if (dup2(pipefd[0], 0) == -1 || dup2(fd, 1) == -1)
	{
		perror("FAILED DUP2 2");
		exit(1);
	}
	close(fd);
	close(pipefd[0]);
}

int	open_file(char *str, int flag)
{
	int	fd;

	fd = -1;
	if (flag == 0)
		fd = open(str, O_RDONLY);
	else if (flag == 1)
		fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("FAILED TO OPEN FILE");
		return (-1);
	}
	return (fd);
}

int	failure_command(int fd[2], char **matrix)
{
	free_mat(matrix);
	write(2, "command not found: ", 19);
	close_fd(fd);
	return (-1);
}
