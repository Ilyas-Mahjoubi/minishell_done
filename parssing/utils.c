/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:55:30 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/12 18:24:48 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built-ins/minishell.h"

t_token *creat_token(char *content, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return NULL;
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return NULL;
	}
	new_token->type = type;
	new_token->next = NULL;
	return new_token;
}
t_token *free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free (tmp->content);
		free(tmp);
	}
	return NULL;
}

t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_token *handle_env_variable(char *input, int *i, t_token *head, t_token **current_word_token, t_info *info)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(*i)++; // Skip the $

	// Handle special case for $? (last exit status)
	if (input[*i] == '?')
	{
		(*i)++; // Skip the '?'

		// Use mdollar function to get exit status
		var_name = ft_strdup("?");
		if (!var_name)
			return free_tokens(head);

		var_value = mdollar(var_name, info);

		free(var_name);

		if (!var_value)
			var_value = ft_strdup(""); // Empty string if not found

		if (!var_value)
			return free_tokens(head);

		head = join_word_segment(var_value, head, current_word_token);
		return head;
	}
	// Handle regular environment variables
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;

	if (*i == start)
		return head; // No valid variable name after $

	var_name = ft_substr(input, start, *i - start);
	if (!var_name)
		return free_tokens(head);

	// Use mdollar function for variable expansion
	var_value = mdollar(var_name, info);
	free(var_name);

	if (!var_value)
		var_value = ft_strdup(""); // Expand to empty if not found

	if (!var_value)
		return free_tokens(head);

	head = join_word_segment(var_value, head, current_word_token);
	return head;
}

