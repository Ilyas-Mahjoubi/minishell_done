/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:47:13 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/10 17:44:40 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(void)
{
	char	*buf; //THE-PATH_MAX-ON-LINUX

	buf = getcwd(NULL, 0); // AUTOMATICALLY ALLOCATES MEMORY NESSCARY FOR  THE PATH
	if (!buf)
	{
		ft_printf(2, "pwd: error while retrieving current directory: getcwd:");
		return (estat(1), NULL);
	}
	return (estat(0), buf);
}

void	print_pwd(void)
{
	char	*pwd;

	pwd = ft_pwd();
	ft_printf(1, "%s\n", pwd);
	free(pwd);
}

/* int	main()
{
	char	*hh;

	hh = ft_pwd();
	printf("%s\n", hh);
	free(hh);
} */
