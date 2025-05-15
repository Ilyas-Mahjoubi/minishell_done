/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intergration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:19:42 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/15 20:03:24 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// wrong place to divide, first just make a matrix for command then inside that allocate
// or just search the matrix for redirections nd do them first
// output always the word after

#include "minishell.h"

void	save_redirections(t_info *info, t_token *token)
{
	t_token *tmp;
	char	**matrix;

	tmp = token;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 3
			|| tmp->type == 4 || tmp->type == 7)
		{
			matrix = malloc(3 * sizeof(char*));
			if (!matrix)
				return ;
			matrix[2] = NULL;
			matrix[0] = ft_strdup(tmp->content);
			matrix[1] = ft_strdup(tmp->next->content);
			info->exec[info->pos] = matrix;
			info->pos++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}


void	save_command(t_info *info, t_token **token)
{
	int		i;
	int		j;
	char	**matrix;
	t_token	*tmp;

	i = 0;
	tmp = *token;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 4
			|| tmp->type == 3 || tmp->type == 7)
			tmp = tmp->next->next;
		// else if (tmp->type == 8 || tmp->type == 6)
		// {
		// 		i += 2;
		// 		tmp = tmp->next;
		// }
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	save_redirections(info, (*token));
	if (i == 0)
	{
		while ((*token) && (*token)->type != 1)
			(*token) = (*token)->next;
		return ;
	}
	matrix = malloc((i + 1) * sizeof(char *));
	if (!matrix)
		return ;
	j = 0;
	while ((*token) && (*token)->type != 1)
	{
		if ((*token)->type != 2 && (*token)->type != 4
			&& (*token)->type != 3 && (*token)->type != 7)
		{
			if (((*token)->type == 5 || (*token)->type == 6) && ((ft_strcmp((*token)->content, "<") == 0
			|| ft_strcmp((*token)->content, ">") == 0
			|| ft_strcmp((*token)->content, ">>") == 0
			|| ft_strcmp((*token)->content, "<<") == 0)))
				matrix[j] = ft_strjoin(";", (*token)->content);
			// else if ((*token)->type == 8)
			// {
			// 	matrix[j] = ft_strdup("$");
			// 	j++;
			// 	matrix[j] = ft_strdup((*token)->content);
			// }
			else
				matrix[j] = ft_strdup((*token)->content);
			j++;
			(*token) = (*token)->next;
		}
		else
			(*token) = (*token)->next->next;
	}
	matrix[j] = NULL;
	info->exec[info->pos] = matrix;
	info->pos++;
	return ;
}

void	save_other(t_info *info, t_token **token)
{
	char	**matrix;

	matrix = malloc(2 * sizeof(char *));
	if (!matrix)
		return ;
	matrix[0] = ft_strdup((*token)->content);
	matrix[1] = NULL;
	(*token) = (*token)->next;
	info->exec[info->pos] = matrix;
	info->pos++;
}

void	ft_conditions(t_info *info, t_token **token)
{
	if ((*token)->type != 1)
		save_command(info, token);
	else
		save_other(info, token);
}

void	form_main(t_token *token, t_info *info)
{
	int		i;
	int		flag;
	int		size;
	t_token	*tmp;
	char	***matrix;

	size = 0;
	flag = 0;
	tmp = token;
	while(tmp)
	{
		if (tmp->type == 0)
			size++;
		while (tmp && tmp->type != 1)
		{
			if (tmp->type == 2 || tmp->type == 4
				|| tmp->type == 3 || tmp->type == 7)
				size++;
			tmp = tmp->next;
		}
		if (tmp && tmp->type == 1)
		{
			size++;
			tmp = tmp->next;
		}
	}
	printf("size: %d", size);
	matrix = malloc((size + 1) * sizeof(char**));
	if (!matrix)
		return ;
	i = size;
	while (i >= 0)
	{
		matrix[i] = NULL;
		i--;
	}
	info->exec = matrix;
	info->pos = 0;
	while (token)
		ft_conditions(info, &token);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_token		*token;
// 	t_token		*token1;
// 	t_info		info;
// 	int	i;
// 	int	j;

// 	(void)ac;
// 	(void)av;
// 	form_env(env, &info);
// 	ft_env(&info);
// 	form_main(token, &info);
// 	i = 0;
// 	while (info.exec[i])
// 	{
// 		j = 0;
// 		arg_execve(&info.exec[i], &info);
// 		while (info.exec[i][j])
// 		{
// 			printf("%s\n", info.exec[i][j]);
// 			j++;
// 		}
// 		printf("----------------------\n");
// 		i++;
// 		fflush(stdout);
// 	}
// 	ft_execution(&info);
// 	// ft_env(&info);
// 	ft_printf(1, "%d: exit_status\n", exit_status);
// }
