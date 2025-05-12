/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <tkurukul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:46:45 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/10 17:25:15 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cd ~ /

#include "minishell.h"

char	*home_path(t_info *info)
{
	int	i;
	char	*str;

	i = 0;
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], "HOME=", 5) == 0)
			str = ft_strdup(info->env[i] + 5);
		i++;
	}
	return (str);
}

int		matlen(char	**matrix)
{
	int		i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

char	**addto_env(char	**matrix, char *str, char *search)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = (int)ft_strlen(search);
	tmp = malloc(((matlen(matrix) + 2) * sizeof(char *)));
	if (!tmp)
		return (NULL);
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], search, len) == 0)
			tmp[j++] = str;
		tmp[j] = ft_strdup(matrix[i]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	free_mat(matrix);
	return (tmp);
}

int	update_oldpwd(char ***matrix)
{
	int	i;
	int		flag;
	char	*oldpwd;
	char	*pwd;
	char	**tmp;

	i = 0;
	flag = 0;
	pwd = ft_pwd();
	if (!pwd)
		return (-1);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (oldpwd == NULL)
		return (-1);
	free(pwd);
	i = 0;
	while((*matrix)[i])
	{
		if (ft_strncmp((*matrix)[i], "OLDPWD=", 7) == 0)
		{
			free((*matrix)[i]);
			(*matrix)[i] = oldpwd;
			flag = 1;
			return (0);
		}
		i++;
	}
	if (flag == 0)
	{
		tmp = addto_env((*matrix), oldpwd, "DOCKER_HOST=");
		if (!tmp)
			return (-1);
		(*matrix) = tmp;
	}
	return (0);
}

int	update_pwd(char ***matrix)
{
	int	i;
	int	flag;
	char	*newpwd;
	char	*join;
	char	**tmp;

	i = 0;
	flag = 0;
	newpwd = ft_pwd();
	join = ft_strjoin("PWD=", newpwd);
	if (join == NULL)
		return (-1);
	while((*matrix)[i])
	{
		if (ft_strncmp((*matrix)[i], "PWD=", 4) == 0)
		{
			free((*matrix)[i]);
			(*matrix)[i] = join;
			flag = 1;
			break;
		}
		i++;
	}
	if (flag == 0)
	{
		tmp = addto_env((*matrix), join, "USER=");
		if (!tmp)
			return (-1);
		(*matrix) = tmp;
	}
	return (0);
}

void	ft_cd(char **args, t_info *info)
{
	char	*home;

	home = home_path(info);
	if (args[2])
		return (ft_printf(2, "MINISHELL: cd: too many arguments\n"), free(home), estat(1));
	if (args[1] == NULL || (ft_strcmp(args[1], "~") == 0))
	{
		update_oldpwd(&info->env);
		chdir((const char*)home);
		update_pwd(&info->env);
		return (free(home), estat(0));
	}
	else if(args[1])
	{
		update_oldpwd(&info->env);
		if (chdir(args[1]) != 0)
			return (ft_printf(2, "Minishell: cd: %s: %s\n", args[1], strerror(errno)), estat(1));
		update_pwd(&info->env);
		return (free(home), estat(0));
	}
	return (free(home), estat(1));
}

// int	main(int ac, char **av, char **env)
// {
// 	t_info	info;
// 	char	*args[2];
// 	// int	i;

// 	// i = 0;
// 	(void)ac;
// 	(void)av;
// 	args[0] = "~/th";
// 	args[1] = NULL;
// 	info.env = NULL;
// 	form_env(env, &info);
// 	// while (info.env[i])
// 	// {
// 	// 	printf("%s\n", info.env[i]);
// 	// 	i++;
// 	// }
// 	// printf("\nBEFORE\n\n\nAFTER\n");
// 	ft_cd(args, &info);
// 	// i = 0;
// 	// while (info.env[i])
// 	// {
// 	// 	printf("%s\n", info.env[i]);
// 	// 	fflush(stdout);
// 	// 	i++;
// 	// }
// }

