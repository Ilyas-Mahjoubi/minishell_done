/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:29:40 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/12 18:50:43 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while that createws forks for every process.; the parent will wait for the child and start the next loop;
// first and last have to have their unused pipes closed in normal use(without redirections).
// redirections have to be exectued after opening fork and before every exectution of command


// intergrate built ins
// in parent after each

#include "minishell.h"

// int	middle_child(int pipefd[2])
// {
// 	if (dup2(pipefd[1], 1) == -1)
// 	{
// 		close_fd(pipefd);
// 		return (-1);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	return (0);
// }

void	one_exec(char **command, t_info *info, int fd[2])
{
	char	*str;

	str = NULL;
	str = abs_path(command[0], info);
	if (!str)
	{
		failure_command(fd, command, &command[0]);
		exit (exit_status);
	}
	execve(str, command, info->env);
	failure(fd);
	free3(info->exec);
	free(str);
	exit (126);
}

int	ft_redirections(char **matrix)
{
	int	result;

	result = 0;
	if (ft_strcmp(matrix[0],"<") == 0)
		result = ft_input(matrix);
	else if (ft_strcmp(matrix[0],">") == 0)
		result = ft_output(matrix);
	else if (ft_strcmp(matrix[0],">>") == 0)
		result = ft_append(matrix);
	else if (ft_strcmp(matrix[0],"<<") == 0)
		result = ft_heredoc(matrix);
	if (result == -1)
		return (-1);
	return (0);
}

int is_redirection(char **matrix)
{
	if (!matrix || !matrix[0])
		return 0;
	return (ft_strcmp(matrix[0], "<") == 0
		|| ft_strcmp(matrix[0], ">") == 0
		|| ft_strcmp(matrix[0], ">>") == 0
		|| ft_strcmp(matrix[0], "<<") == 0);
}

int is_builtin(char **matrix)
{
	if (!matrix || !matrix[0])
		return (0);
	if (ft_strcmp(matrix[0], "cd") == 0
		|| ft_strcmp(matrix[0], "pwd") == 0
		|| ft_strcmp(matrix[0], "unset") == 0
		|| ft_strcmp(matrix[0], "export") == 0
		|| ft_strcmp(matrix[0], "env") == 0
		|| ft_strcmp(matrix[0], "echo") == 0
		|| ft_strcmp(matrix[0], "exit") == 0)
		return (1);
	return (0);
}

void exec_builtin(char **matrix, t_info *info)
{
	if (ft_strcmp(matrix[0], "cd") == 0)
		ft_cd(matrix, info);
	else if (ft_strcmp(matrix[0], "pwd") == 0)
		print_pwd();
	else if (ft_strcmp(matrix[0], "unset") == 0)
		ft_unset(info, matrix);
	else if (ft_strcmp(matrix[0], "export") == 0)
		ft_export(info, matrix);
	else if (ft_strcmp(matrix[0], "env") == 0)
		ft_env(info);
	else if (ft_strcmp(matrix[0], "echo") == 0)
		ft_echo(matrix);
	else if (ft_strcmp(matrix[0], "exit") == 0)
		ft_exit(matrix);
}

int	istt_builtin(char ***matrix, t_info *info)
{
	int	i;
	int	mat;

	i = 0;
	mat = 0;
	while(is_redirection(matrix[mat]))
	{
		ft_redirections(info->exec[mat]);
		mat++;
	}
	i = 0;
	if (ft_strcmp(matrix[mat][0], "cd") == 0)
		ft_cd(matrix[mat], info);
	else if (ft_strcmp(matrix[mat][0], "pwd") == 0)
		print_pwd();
	else if (ft_strcmp(matrix[mat][0], "unset") == 0)
		ft_unset(info, matrix[mat]);
	else if (ft_strcmp(matrix[mat][0], "export") == 0)
		ft_export(info, matrix[mat]);
	else if (ft_strcmp(matrix[mat][0], "env") == 0)
		ft_env(info);
	else if (ft_strcmp(matrix[mat][0], "echo") == 0)
		ft_echo(matrix[mat]);
	else if (ft_strcmp(matrix[mat][0], "exit") == 0)
		ft_exit(matrix[mat]);
	else
		i = -1;
	return (i);
}

int	is_only_redirection(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (!(matrix[i][0]) ||
			!(ft_strcmp(matrix[i][0], "<") == 0 ||
			  ft_strcmp(matrix[i][0], ">") == 0 ||
			  ft_strcmp(matrix[i][0], "<<") == 0 ||
			  ft_strcmp(matrix[i][0], ">>") == 0))
			return (-1);
		i++;
	}
	return (0);
}



void	ft_execution(t_info *info)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	mat;
	int	count;
	int	cpipe[2];
	int	prevpipe;
	pid_t	pid;
	int		status;

	i = 0;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	count = 0;
	prevpipe = -42;
	while (info->exec[i])
	{
		if (ft_isalpha(info->exec[i][0][0]) == 1 || is_redirection(info->exec[i]))
			count++;
		i++;
	}
	i = 0;
	mat = 0;
	while (i < count)
	{
		if (is_only_redirection(info->exec) == 0)
		{
			while(info->exec[mat])
			{
				ft_redirections(info->exec[mat]);
				mat++;
			}
			ft_refresh_fd(fd_in, fd_out);
			break;
		}
		if (count == 1)
		{
			if (istt_builtin(info->exec, info) != -1)
			{
				ft_refresh_fd(fd_in, fd_out);
				break;
			}
		}
		if (i != (count - 1))
		{
			if (pipe(cpipe) == -1)
			{
				ft_printf(2, "Minishell: error pipe\n");
					return (estat(1));
			}
		}
		pid = fork();
		if (pid == -1)
		{
			ft_printf(2, "Minishell: error fork");
			exit(1);
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i != 0)
			{
				if (dup2(prevpipe, 0) == -1)
					return (ft_printf(2, "1Minishell: error dup2\n"), exit(1));
				close(prevpipe);
			}
			if (i != (count - 1))
			{
				close(cpipe[0]);
				if (dup2(cpipe[1], 1) == -1)
					return (ft_printf(2, "2Minishell: error dup2\n"), exit(1));
				close(cpipe[1]);
			}
			while (is_redirection(info->exec[mat]))
			{
				if (ft_redirections(info->exec[mat]) == -1)
					return (exit(1));
				mat++;
			}
			if (!info->exec[mat])
				return ;
			if (is_builtin(info->exec[mat]))
			{
				exec_builtin(info->exec[mat], info);
				exit(0);
			}
			else
				one_exec(info->exec[mat], info, cpipe);
		}
		else
		{
			while (info->exec[mat])
			{
				if (info->exec[mat][0][0] == '|')
				{
					mat++;
					break;
				}
				mat++;
			}
			if (prevpipe != -42)
				close(prevpipe);
			if (i != (count -1))
			{
				close(cpipe[1]);
				prevpipe = cpipe[0];
			}
			if (waitpid(pid, &status, 0) == -1)
			{
				ft_printf(2, "Minishell: error waitpid\n");
				free3(info->exec);
				exit(1);
			}
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free3(info->exec);
	ft_refresh_fd(fd_in, fd_out);
	close(fd_in);
	close(fd_out);
}


