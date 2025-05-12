/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:23:50 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/08 16:11:03 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= 0 && str[i] <= 9)
			i++;
		else
			return (-1);
	}
	return (0);
}

void	ft_exit(char **args)
{
	ft_printf(1, "exit\n");
	if (args[1])
	{
		if (is_num(args[1]) == -1 && !args[2])
		{
			ft_printf(2, "Minishell: exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		if (args[2])
		{
			ft_printf(2,"Minishell: exit: too many arguments\n");
			return ;
		}
		exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}
