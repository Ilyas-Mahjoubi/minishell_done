/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:48:21 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/08 18:30:17 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for args
// if dont exisit do nothing but do other args
// return success if no args
// tmp
// mat_remove
// when returning the status of the signal global variable should change (ex; exit(0) || exit(1))


int	calcu(char **args, t_info *info)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (args[i])
	{
		// control any dupes because you remove only once because if not it will count multiple dups.
		if (exisit(info->tmp, args[i]) != -1 && verify_equal(args[i]) == -1)
			size++;
		i++;
	}
	return (size);
}

int	dups(char **args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strcmp(args[i], args[j]) == 0)
			{
				count++;
				break;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	yes_unset(t_info *info, char **args, int i)
{
	int	x;
	int	len;

	x = 1;
	while (args[x])
	{
		len = ft_strlen(args[x]);
		if (ft_strncmp(args[x], info->tmp[i], len) == 0 && info->tmp[i][len] == '=' && verify_equal(args[x]) == -1)
			return (1);
		x++;
	}
	return (0);
}

static void	proccess(t_info *info, char **args)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (info->tmp[i])
		i++;
	size = i - (calcu(args, info) - dups(args));
	info->env = malloc((size + 1) * sizeof(char *));
	if (!info->env)
		return (estat(1));
	i = 0;
	j = 0;
	while (info->tmp[i])
	{
		if (yes_unset(info, args, i) == 0)
		{
			info->env[j] = ft_strdup(info->tmp[i]);
			j++;
		}
		i++;
	}
	info->env[j] = NULL;
	free_mat(info->tmp);
}
// calculate how many have to be removed with exisit, malloc matrix - remove args
// strcmp with arg and variables in tmp and strdup the !=;
// save in env


void	ft_unset(t_info *info, char **args)
{
	if (!args[1])
		return (estat(1));
	matrix_tmp(info);
	free_mat(info->env);
	proccess(info, args);
	return (estat(0));
}

/* int	main(int ac, char **av, char **env)
{
	t_info	info;
	char	*args[4];
	char	*fix[2];
	int	i;

	i = 0;
	(void)ac;
	(void)av;
	fix[0] = "fic=1";
	fix[1] = NULL;
	args[0] = "HOME";
	args[1] = "USER";
	args[2] = "fic=1";
	args[3] = NULL;
	info.env = NULL;
	form_env(env, &info);
	ft_export(&info, fix);
	ft_unset(&info, args);
	while (info.env[i])
	{
		printf("%s\n", info.env[i]);
		i++;
	}
	free_mat(info.env);
	// printf("\nBEFORE\n\n\nAFTER\n");
	// i = 0;
	// while (info.env[i])
	// {
	// 	printf("%s\n", info.env[i]);
	// 	fflush(stdout);
	// 	i++;
	// }
} */

