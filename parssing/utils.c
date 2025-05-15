/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:55:30 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/15 21:50:58 by ilmahjou         ###   ########.fr       */
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
// for try//
t_token *expand_and_tokenize_var(char *var_value, t_info *info)
{
	if (!var_value || !*var_value)
		return NULL;
	char *var_copy = ft_strdup(var_value);
	if (!var_copy)
		return NULL;
	t_token *expanded_tokens = tokenize_string(var_copy, info);
	free(var_copy);
	return expanded_tokens;
}

/* t_token *tokenize_string(char *str, t_info *info)
{
	t_token *head = NULL;
	t_token *current_word_token = NULL;
	int     i = 0;
	char    *segment = NULL;

	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t') // Space - end of current word
		{
			current_word_token = NULL; // Reset current word
			i++;
		}
		else if (str[i] == '|') // Pipe
		{
			current_word_token = NULL; // Reset current word
			head = handle_pipe(&i, head, get_last_token(head));
		}
		else if (str[i] == '<' || str[i] == '>') // Redirection
		{
			current_word_token = NULL; // Reset current word
			head = handle_redirection(str, &i, head, get_last_token(head));
		}
		else if (str[i] == '\'') // Single quotes
		{
			segment = extract_single_quote_content(str, &i);
			if (!segment)
				return (free_tokens(head));
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (str[i] == '"') // Double quotes
		{
			segment = extract_double_quote_content(str, &i, info);
			if (!segment)
				return (free_tokens(head));
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (str[i] == '$') // Variable
		{
			head = handle_env_variable(str, &i, head, &current_word_token, info);
		}
		else // Regular word character
		{
			segment = extract_word_segment(str, &i);
			if (segment)
				head = join_word_segment(segment, head, &current_word_token);
		}
		if (!head)
			return (NULL);
	}
	return (head);
} */

t_token *tokenize_string(char *str, t_info *info)
{
	t_token *head = NULL;
	t_token *current_word_token = NULL;
	int     i = 0;
	char    *segment = NULL;

	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			current_word_token = NULL;
			i++;
		}
		else if (str[i] == '|')
		{
			current_word_token = NULL;
			head = handle_pipe(&i, head, get_last_token(head));
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			current_word_token = NULL;
			head = handle_redirection(str, &i, head, get_last_token(head));
		}
		else if (str[i] == '\'')
		{
			segment = extract_single_quote_content(str, &i);
			if (!segment)
				return (free_tokens(head));
			// Pass TOKEN_SQUOTE for single-quoted segments
			head = join_word_segment(segment, head, &current_word_token, TOKEN_SQUOTE);
		}
		else if (str[i] == '"')
		{
			segment = extract_double_quote_content(str, &i, info);
			if (!segment)
				return (free_tokens(head));
			// Pass TOKEN_DQUOTE for double-quoted segments
			head = join_word_segment(segment, head, &current_word_token, TOKEN_DQUOTE);
		}
		else if (str[i] == '$')
		{
			head = handle_env_variable(str, &i, head, &current_word_token, info);
		}
		else
		{
			segment = extract_word_segment(str, &i);
			if (segment)
				// Default to TOKEN_WORD for unquoted text
				head = join_word_segment(segment, head, &current_word_token, TOKEN_WORD);
		}
		if (!head)
			return (NULL);
	}
	return (head);
}

t_token *handle_env_variable(char *input, int *i, t_token *head,
                           t_token **current_word_token, t_info *info)
{
	int start;
	char *var_name;
	char *var_value;
	t_token *expanded_tokens = NULL;
	t_token *last_token;
	int dollar_pos = *i;
	t_token_type current_type = (*current_word_token) ? (*current_word_token)->type : TOKEN_WORD;

	(*i)++; // Skip '$'

	// Handle $? special case
	if (input[*i] == '?')
	{
		(*i)++;
		var_value = mdollar("?", info);
		if (!var_value)
			var_value = ft_strdup("");
		if (!var_value)
			return free_tokens(head);

		head = join_word_segment(var_value, head, current_word_token, current_type);
		free(var_value);
		return head;
	}

	// Check for valid variable name
	if (!input[*i] || !(ft_isalpha(input[*i]) || input[*i] == '_'))
	{
		*i = dollar_pos; // Rewind to $
		char *dollar_str = ft_strdup("$");
		if (!dollar_str)
			return free_tokens(head);

		head = join_word_segment(dollar_str, head, current_word_token, current_type);
		(*i)++;
		return head;
	}

	// Extract variable name
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;

	var_name = ft_substr(input, start, *i - start);
	if (!var_name)
		return free_tokens(head);

	// Get variable value
	var_value = mdollar(var_name, info);
	free(var_name);

	// Check quote context
	int in_quotes = 0;
	for (int j = 0; j < dollar_pos; j++)
		if (input[j] == '"' || input[j] == '\'')
			in_quotes = !in_quotes;

	// Handle empty/unset variables
	if (!var_value || !*var_value)
	{
		var_value = ft_strdup("");
		if (!var_value)
			return free_tokens(head);
	}

	// In quotes or building existing word: join as segment
	if (in_quotes || *current_word_token)
	{
		head = join_word_segment(var_value, head, current_word_token,
								in_quotes ? TOKEN_DQUOTE : current_type);
		free(var_value);
		return head;
	}

	// Not in quotes and new word: tokenize the expansion
	expanded_tokens = expand_and_tokenize_var(var_value, info);
	free(var_value);

	if (!expanded_tokens)
		return head;

	if (!head)
		head = expanded_tokens;
	else
	{
		last_token = get_last_token(head);
		last_token->next = expanded_tokens;
	}
	return head;
}

