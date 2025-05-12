/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:07:45 by tkurukul          #+#    #+#             */
/*   Updated: 2025/03/01 18:19:46 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_one(char **av, int fd[2], char **envp)
{
	char	**matrix;
	char	*str;
	int		file;

	close(fd[0]);
	str = NULL;
	file = open_file(av[1], 0);
	if (file == -1)
		return (-1);
	in_out_1(fd, file);
	matrix = matrix_creation(av[2]);
	if (!matrix)
		return (-1);
	str = abs_path(matrix[0], envp);
	if (!str)
	{
		failure_command(fd, matrix);
		return (-1);
	}
	execve(str, matrix, envp);
	failure(fd, "EXECVE FAILED");
	free_mat(matrix);
	free(str);
	return (-1);
}

int	child_two(char **av, int fd[2], char **envp)
{
	char	**matrix;
	char	*str;
	int		file;

	close(fd[1]);
	str = NULL;
	file = open_file(av[4], 1);
	if (file == -1)
		return (-1);
	in_out_2(fd, file);
	matrix = matrix_creation(av[3]);
	if (!matrix)
		return (-1);
	str = abs_path(matrix[0], envp);
	if (!str)
	{
		failure_command(fd, matrix);
		return (-1);
	}
	execve(str, matrix, envp);
	failure(fd, "EXECVE FAILED");
	free_mat(matrix);
	free(str);
	return (-1);
}

char	**find_path(char **envp)
{
	int		i;
	char	*str;
	char	**matrix;

	str = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			str = (envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!str)
		return (NULL);
	matrix = ft_split(str, ':');
	return (matrix);
}

char	*build_full(char *path, char *command)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, command);
	free (tmp);
	return (str);
}

char	*abs_path(char *command, char **envp)
{
	int		i;
	char	**matrix;
	char	*str;

	i = 0;
	matrix = find_path(envp);
	if (!matrix)
		return (NULL);
	while (matrix[i])
	{
		if (i == 0)
			str = ft_strdup(command);
		else
			str = build_full(matrix[i], command);
		if (access(str, X_OK) == 0)
			return (free_mat(matrix), str);
		i++;
		free(str);
	}
	free_mat(matrix);
	return (NULL);
}
