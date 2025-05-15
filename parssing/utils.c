/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:55:30 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/15 16:26:41 by ilmahjou         ###   ########.fr       */
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

t_token *tokenize_string(char *str, t_info *info)
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
}

/* t_token *handle_env_variable(char *input, int *i, t_token *head, t_token **current_word_token, t_info *info)
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
} */

/* t_token *handle_env_variable(char *input, int *i, t_token *head, t_token **current_word_token, t_info *info)
{
    int     start;
    char    *var_name;
    char    *var_value;
    t_token *expanded_tokens = NULL;
    t_token *last_token;

    (*i)++; // Skip the $

    // Handle special case for $? (last exit status)
    if (input[*i] == '?')
    {
        (*i)++; // Skip the '?'
        var_name = ft_strdup("?");
        if (!var_name)
            return free_tokens(head);
        var_value = mdollar(var_name, info);
        free(var_name);
        if (!var_value)
            var_value = ft_strdup("");
        if (!var_value)
            return free_tokens(head);
        // For $?, we don't tokenize the result, just join it as a word segment
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

    // Get variable value
    var_value = mdollar(var_name, info);
    free(var_name);

    // Check if we are in a quote context
    int in_quotes = 0;
    int j = 0;
    while (j < *i)
    {
        if (input[j] == '"' || input[j] == '\'')
            in_quotes = !in_quotes;
        j++;
    }

    // If in quotes or no value, just add as a word segment
    if (in_quotes || !var_value || !*var_value)
    {
        if (!var_value)
            var_value = ft_strdup("");

        if (!var_value)
            return free_tokens(head);

        head = join_word_segment(var_value, head, current_word_token);
        return head;
    }

    // If we're not in quotes, and the current word token is empty,
    // we can tokenize the expanded value
    if (*current_word_token == NULL)
    {
        // Tokenize the variable value
        expanded_tokens = expand_and_tokenize_var(var_value, info);
        free(var_value);

        // If tokenization failed or produced no tokens
        if (!expanded_tokens)
            return head;

        // Append the expanded tokens to the token list
        if (!head)
            head = expanded_tokens;
        else
        {
            last_token = get_last_token(head);
            last_token->next = expanded_tokens;
        }
    }
    else
    {
        // If we're already building a word, just append the value
        head = join_word_segment(var_value, head, current_word_token);
    }

    return head;
} */

/* t_token *handle_env_variable(char *input, int *i, t_token *head, t_token **current_word_token, t_info *info)
{
	int	start;
	char	*var_name;
	char	*var_value;
	t_token	*expanded_tokens = NULL;
	t_token	*last_token;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++; // Skip the '?'
		var_name = ft_strdup("?");
		if (!var_name)
			return free_tokens(head);
		var_value = mdollar(var_name, info);
		free(var_name);
		if (!var_value)
			var_value = ft_strdup("");
		if (!var_value)
			return free_tokens(head);
		// For $?, we don't tokenize the result, just join it as a word segment
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

	// Get variable value
	var_value = mdollar(var_name, info);
	free(var_name);

	// Check if we are in a quote context
	int in_quotes = 0;
	int j = 0;
	while (j < *i)
	{
		if (input[j] == '"' || input[j] == '\'')
			in_quotes = !in_quotes;
		j++;
	}

	// If in quotes or no value, just add as a word segment
	if (in_quotes || !var_value || !*var_value)
	{
		if (!var_value)
			var_value = ft_strdup("");

		if (!var_value)
			return free_tokens(head);

		head = join_word_segment(var_value, head, current_word_token);
		return head;
	}

	// If we're not in quotes, and the current word token is empty,
	// we can tokenize the expanded value
	if (*current_word_token == NULL)
	{
		// Tokenize the variable value
		expanded_tokens = expand_and_tokenize_var(var_value, info);
		free(var_value);

		// If tokenization failed or produced no tokens
		if (!expanded_tokens)
			return head;

		// Append the expanded tokens to the token list
		if (!head)
			head = expanded_tokens;
		else
		{
			last_token = get_last_token(head);
			last_token->next = expanded_tokens;
		}
	}
	else
	{
		// If we're already building a word, just append the value
		head = join_word_segment(var_value, head, current_word_token);
	}

	return head;
} */

t_token *handle_env_variable(char *input, int *i, t_token *head, t_token **current_word_token, t_info *info)
{
	int     start;
	char    *var_name;
	char    *var_value;
	t_token *expanded_tokens = NULL;
	t_token *last_token;

	// Store the original position of the $
	int dollar_pos = *i;

	(*i)++; // Skip the '$'

	// Check for $? special case
	if (input[*i] == '?')
	{
		(*i)++; // Skip the '?'
		var_name = ft_strdup("?");
		if (!var_name)
			return free_tokens(head);
		var_value = mdollar(var_name, info);
		free(var_name);
		if (!var_value)
			var_value = ft_strdup("");
		if (!var_value)
			return free_tokens(head);
		// For $?, we don't tokenize the result, just join it as a word segment
		head = join_word_segment(var_value, head, current_word_token);
		return head;
	}

	// Check if the character after $ is a valid variable name starter
	// (letter or underscore, according to POSIX)
	if (!input[*i] || !(ft_isalpha(input[*i]) || input[*i] == '_'))
	{
		// Not a valid variable name, treat $ as a literal character
		// Reset the position to where the $ was
		*i = dollar_pos;

		// Create a segment with just the $ character
		char *dollar_str = ft_strdup("$");
		if (!dollar_str)
			return free_tokens(head);

		head = join_word_segment(dollar_str, head, current_word_token);
		(*i)++; // Skip the $ since we've handled it
		return head;
	}

	// Handle regular environment variables
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;

	if (*i == start) // This should not happen now given our checks above
		return head;

	var_name = ft_substr(input, start, *i - start);
	if (!var_name)
		return free_tokens(head);

	// Get variable value
	var_value = mdollar(var_name, info);
	free(var_name);

	// Check if we are in a quote context
	int in_quotes = 0;
	int j = 0;
	while (j < dollar_pos)
	{
		if (input[j] == '"' || input[j] == '\'')
			in_quotes = !in_quotes;
		j++;
	}

	// If in quotes or no value, just add as a word segment
	if (in_quotes || !var_value || !*var_value)
	{
		if (!var_value)
			var_value = ft_strdup("");

		if (!var_value)
			return free_tokens(head);

		head = join_word_segment(var_value, head, current_word_token);
		return head;
	}

	// If we're not in quotes, and the current word token is empty,
	// we can tokenize the expanded value
	if (*current_word_token == NULL)
	{
		// Tokenize the variable value
		expanded_tokens = expand_and_tokenize_var(var_value, info);
		free(var_value);

		// If tokenization failed or produced no tokens
		if (!expanded_tokens)
			return head;

		// Append the expanded tokens to the token list
		if (!head)
			head = expanded_tokens;
		else
		{
			last_token = get_last_token(head);
			last_token->next = expanded_tokens;
		}
	}
	else
	{
		// If we're already building a word, just append the value
		head = join_word_segment(var_value, head, current_word_token);
	}

	return head;
}

