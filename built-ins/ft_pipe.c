/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:52:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/06 23:44:52 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// in this file handle processes
// a while commands exisit i have to check all the redirections. so no
// handle one command
// first proccess : middle procceses : last proccess

// cannot do it this way, make a single process; with redirections

#include "minishell.h"

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

char	*abs_path(char *command, t_info *info)
{
	int		i;
	char	**matrix;
	char	*str;

	i = 0;
	matrix = find_path(info->env);
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

// int	child_one(char **commands, int fd[2], t_info *info)
// {
// 	char	*str;
// 	int		file;

// 	close(fd[0]);
// 	str = NULL;
// 	if (in_out_1(fd) == -1)
// 		return (-1);
// 	str = abs_path(commands[0], info->env);
// 	if (!str)
// 	{
// 		failure_command(fd, commands);
// 		return (-1);
// 	}
// 	execve(str, commands, info->env);
// 	failure(fd, "EXECVE FAILED");
// 	free_mat(commands);
// 	//free_mat_mat for other commands
// 	free(str);
// 	return (-1);
// }

// int		middle_child(char *commands, int fd[2], t_info *info)
// {
// 	char	*str;
// 	int		file;

// 	str = NULL;
// 	if (in_out_1(fd) == -1)
// 		return (-1);
// 	str = abs_path(commands[0], info->env);
// 	if (!str)
// 	{
// 		failure_command(fd, commands);
// 		return (-1);
// 	}
// 	execve(str, commands, info->env);
// 	failure(fd, "EXECVE FAILED");
// 	free_mat(commands);
// 	//free_mat_mat for other commands
// 	free(str);
// 	return (-1);
// }

// int	child_two(char **av, int fd[2], char **envp)
// {
// 	char	**matrix;
// 	char	*str;
// 	int		file;

// 	close(fd[1]);
// 	str = NULL;
// 	file = open_file(av[4], 1);
// 	if (file == -1)
// 		return (-1);
// 	in_out_2(fd, file);
// 	matrix = matrix_creation(av[3]);
// 	if (!matrix)
// 		return (-1);
// 	str = abs_path(matrix[0], envp);
// 	if (!str)
// 	{
// 		failure_command(fd, matrix);
// 		return (-1);
// 	}
// 	execve(str, matrix, envp);
// 	failure(fd, "EXECVE FAILED");
// 	free_mat(matrix);
// 	free(str);
// 	return (-1);
// }

// void	ft_pipex(char ***matrix, t_info *info)
// {
// 	int	i;
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		return ; // remember to implement the global status code.
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		return (failure(fd, "FORK FAILED"), 1);
// 	if (pid1 == 0 && child_one(*matrix[0], fd, info->env) == -1)
// 		return (close_fd(fd));
// 	if (!*matrix[1])
// 		return (close_fd(fd));
// 	i = 1;
// 	while (matrix[i])
// 	{

// 	}

// }
