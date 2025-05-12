/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:50 by tkurukul          #+#    #+#             */
/*   Updated: 2025/03/01 16:39:17 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		return (write(2, "INCORRECT INPUT FOR PROGRAM\n", 28), 1);
	if (pipe(pipefd) == -1)
		return (perror("PIPE FAILED"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (failure(pipefd, "FORK FAILED"), 1);
	if (pid1 == 0 && child_one(av, pipefd, envp) == -1)
		return (close_fd(pipefd), exit(1), 1);
	pid2 = fork();
	if (pid2 == -1)
		return (failure(pipefd, "FORK FAILED"), 1);
	if (pid2 == 0 && child_two(av, pipefd, envp) == -1)
		return (close_fd(pipefd), exit(1), 1);
	close_fd(pipefd);
	wait_for_process(pid1, pid2);
	return (0);
}
