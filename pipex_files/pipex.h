/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:33:29 by tkurukul          #+#    #+#             */
/*   Updated: 2025/03/01 19:51:31 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libprintf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
// alias valgrind --leak-check=full  --show-leak-kinds=all
//  --track-origins=yes  --track-fds=yes  --trace-children=yes
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>

void	close_fd(int *ar);
int		failure(int fd[2], char *str);
int		failure_command(int fd[2], char **matrix);
int		open_file(char *str, int flag);
void	in_out_2(int pipefd[2], int fd);
void	in_out_1(int pipefd[2], int fd);
char	**matrix_creation(char *str);
void	free_mat(char **matrix);
int		child_one(char **av, int fd[2], char **envp);
int		child_two(char **av, int fd[2], char **envp);
void	wait_for_process(int pid1, int pid2);
char	**find_path(char **envp);
char	*build_full(char *path, char *command);
char	*abs_path(char *command, char **envp);

#endif
