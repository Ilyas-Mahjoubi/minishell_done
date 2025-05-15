/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:47:35 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/15 16:52:35 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// go inside double quotes and single quotes

#include "minishell.h"

int exit_status = 0;

char	*setfull(char *gg, char *str, int size)
{
	char	*tmp;
	int		len;
	char	*full;

	len = ft_strlen(str) - size;
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strncpy(tmp, str + size, len);
	tmp[len] = '\0';
	// printf("tmp = %s\n", tmp);
	full = ft_strjoin(gg, tmp);
	free(tmp);
	return (full);
}

char	*mdollar(char *str, t_info *info)
{
	char	*line;
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (str[0] == '?')
		return (ft_itoa(exit_status));
	else if (str[0] >= '0' && str[0] <= '9')
		return(ft_strdup(str + 1));
	while(info->env[i])
	{
		if (ft_strncmp(info->env[i], str, len) == 0)
		{
			line = ft_strdup(info->env[i] + (len+ 1));
			return (line);
		}
		i++;
	}
	return (NULL);
}

// char	*dollarfull(char *str, t_info *info)
// {
// 	char	*dollar;
// 	char	*gg;
// 	char	*full;
// 	int		i;

// 	i = 0;
// 	while ((str[i] >= 'a' && str[i] <= 'z') || ((str[i] >= 'A' && str[i] <= 'Z')) || str[i] == '_'
// 		|| (str[i] >= '0' && str[i] <= '9') || str[i] == 61 || str[i] == '?')
// 		i++;
// 	dollar = malloc((i + 1) * sizeof(char));
// 	if (!dollar)
// 		return (estat(1), NULL);
// 	ft_strncpy(dollar, str, i);
// 	dollar[i] = '\0';
// 	// printf("dollar = %s\n", dollar);
// 	gg = mdollar(dollar, info);
// 	// printf("gg = %s\n", gg);
// 	free(dollar);
// 	if (!gg)
// 		gg = ft_strdup("");
// 	full = setfull(gg, str, i);
// 	free(gg);
// 	return (full);
// }

// int	arg_execve2(char ***command, int flag)
// {
// 	int	i;
// 	int	j;
// 	char	**tmp;

// 	i = 0;
// 	while ((*command)[i])
// 		i++;
// 	tmp = malloc((i - flag + 1) * sizeof(char *));
// 	if (!tmp)
// 		return (estat(1), -1);
// 	i = 0;
// 	j = 0;
// 	while ((*command)[i])
// 	{
// 		if (ft_strcmp((*command)[i], "flagbyme") != 0)
// 		{
// 			tmp[j] = ft_strdup((*command)[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	tmp[j] = NULL;
// 	free_mat((*command));
// 	(*command) = tmp;
// 	return (0);
// }

// int	arg_execve(char ***command, t_info *info)
// {
// 	int	i;
// 	int	flag;
// 	char	*expansion;

// 	i = 0;
// 	flag = 0;
// 	while ((*command)[i] && (*command)[i + 1])
// 	{
// 		if ((*command)[i][0] == '$')
// 		{
// 			if ((*command)[i + 1][0] == ';')
// 			{
// 				expansion = ft_strdup((*command)[i + 1] + 1);
// 				free((*command)[i + 1]);
// 				(*command)[i + 1] = expansion;
// 				break;
// 			}
// 			if ((*command)[i + 1][0] == ':')
// 			{
// 				expansion = ft_strdup((*command)[i + 1] + 1);
// 				free((*command)[i + 1]);
// 				(*command)[i + 1] = expansion;
// 				free (expansion);
// 			}
// 			flag++;
// 			expansion = dollarfull((*command)[i + 1], info);
// 			if (!expansion)
// 				return (-1);
// 			free((*command)[i]);
// 			(*command)[i] = ft_strdup("flagbyme");
// 			free((*command)[i + 1]);
// 			(*command)[i + 1] = expansion;
// 		}
// 		if ((*command)[i + 1][0] == ';' || (*command)[i + 1][0] == ':')
// 		{
// 			expansion = ft_strdup((*command)[i + 1] + 1);
// 			free((*command)[i + 1]);
// 			(*command)[i + 1] = expansion;
// 		}
// 		i++;
// 	}
// 	if (flag != 0)
// 	{
// 		if (arg_execve2(command, flag) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

/* int	main(int ac, char **av, char **env)
{
	t_info	info;
	char	*f;

	(void)ac;
	(void)av;
	form_env(env, &info);
	exit_status = 2;
	f = dollarfull("?", &info);
	printf("%s\n", f);
	free (f);
	free_mat(info.env);
} */
