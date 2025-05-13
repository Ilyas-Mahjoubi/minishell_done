/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellnorm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:22:23 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/13 18:20:48 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built-ins/minishell.h"

t_token	*handle_pipe(int *i, t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = creat_token("|", TOKEN_PIPE);
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	(*i)++;
	return (head);
}

t_token	*handle_redirection(char *input, int *i, t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			new_token = creat_token("<<", TOKEN_HEREDOC);
			*i += 2;
		}
		else
		{
			new_token = creat_token("<", TOKEN_REDIR_IN);
			(*i)++;
		}
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			new_token = creat_token(">>", TOKEN_REDIR_APPEND);
			*i += 2;
		}
		else
		{
			new_token = creat_token(">", TOKEN_REDIR_OUT);
			(*i)++;
		}
	}
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	return (head);
}

// New function to join adjacent segments into one word
t_token *join_word_segment(char *segment, t_token *head, t_token **current_word_token)
{
	char *new_content;
	t_token *new_token;

	if (!segment)
		return (free_tokens(head));

	if (*current_word_token == NULL)
	{
		// No current word being built, create a new token
		new_token = creat_token(segment, TOKEN_WORD);
		free(segment);
		if (!new_token)
			return (free_tokens(head));

		if (!head)
			head = new_token;
		else
			get_last_token(head)->next = new_token;

		*current_word_token = new_token;
	}
	else
	{
		// Append to existing word token
		new_content = ft_strjoin((*current_word_token)->content, segment);
		free(segment);
		if (!new_content)
			return (free_tokens(head));

		free((*current_word_token)->content);
		(*current_word_token)->content = new_content;
	}

	return (head);
}

// Modified handle_word to extract word segment
char *extract_word_segment(char *input, int *i)
{
	int start;
	//char *word;

	start = *i;
	while (input[*i] && !ft_strchr(" \t|><\'\"$", input[*i]))
		(*i)++;

	if (*i > start)
		return ft_substr(input, start, *i - start);
	return NULL;
}

// Modified handle_single_quotes to return string content
char *extract_single_quote_content(char *input, int *i)
{
	int content_start = *i + 1; // Skip the opening quote
	char quote_char = input[*i];
	char *content;

	(*i)++; // Skip the opening quote

	// Find the closing quote
	while (input[*i] && input[*i] != quote_char)
		(*i)++;

	if (!input[*i]) // No closing quote found
	{
		printf("error: unclosed quote\n");
		return NULL;
	}

	content = ft_substr(input, content_start, *i - content_start);
	(*i)++; // Skip the closing quote
	return content;
}

char *extract_double_quote_content(char *input, int *i, t_info *info)
{
    int     content_start = *i + 1; // Skip the opening quote
    char    quote_char = '"';
    char    *full_segment = NULL;
    //size_t  segment_len = 0;

    (*i)++; // Skip the opening quote

    // Collect all characters within quotes
    while (input[*i] && input[*i] != quote_char)
    {
        if (input[*i] == '$' &&
            (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_' || input[*i + 1] == '?'))
        {
            // Add text before variable
            if (*i > content_start)
            {
                char *pre_var_segment = ft_substr(input, content_start, *i - content_start);
                if (!pre_var_segment)
                {
                    free(full_segment);
                    return NULL;
                }

                // Dynamically reallocate full_segment
                char *temp = full_segment
                    ? ft_strjoin(full_segment, pre_var_segment)
                    : ft_strdup(pre_var_segment);

                free(full_segment);
                free(pre_var_segment);
                full_segment = temp;

                if (!full_segment)
                    return NULL;
            }

            // Process environment variable
            char *var_value = NULL;
            int var_start = *i + 1;

            // Handle $? special case
            if (input[var_start] == '?')
            {
                var_value = mdollar("?", info);
                *i += 2;
            }
            else
            {
                // Find end of variable name
                while (input[*i] && (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_'))
                    (*i)++;

                char *var_name = ft_substr(input, var_start, *i - var_start + 1);
                var_value = mdollar(var_name, info);
                free(var_name);
                (*i)++;
            }

            // Add variable value to full_segment
            if (var_value)
            {
                char *temp = full_segment
                    ? ft_strjoin(full_segment, var_value)
                    : ft_strdup(var_value);

                free(full_segment);
                free(var_value);
                full_segment = temp;

                if (!full_segment)
                    return NULL;
            }

            content_start = *i;
        }
        else
            (*i)++;
    }

    // Add any remaining text
    if (*i > content_start)
    {
        char *final_segment = ft_substr(input, content_start, *i - content_start);
        if (!final_segment)
        {
            free(full_segment);
            return NULL;
        }

        char *temp = full_segment
            ? ft_strjoin(full_segment, final_segment)
            : ft_strdup(final_segment);

        free(full_segment);
        free(final_segment);
        full_segment = temp;

        if (!full_segment)
            return NULL;
    }

    if (!input[*i]) // No closing quote found
    {
        free(full_segment);
        return NULL;
    }

    (*i)++; // Skip the closing quote

    // If no segment was created, return empty string
    return full_segment ? full_segment : ft_strdup("");
}

t_token *tokenize_input(char *input, t_info *info)
{
	t_token *head = NULL;
	t_token *current_word_token = NULL;
	int     i = 0;
	char    *segment = NULL;

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t') // Space - end of current word
		{
			current_word_token = NULL; // Reset current word
			i++;
		}
		else if (input[i] == '|') // Pipe - end of current word and command
		{
			current_word_token = NULL; // Reset current word
			head = handle_pipe(&i, head, get_last_token(head));
		}
		else if (input[i] == '<' || input[i] == '>') // Redirection - end of current word
		{
			current_word_token = NULL; // Reset current word
			head = handle_redirection(input, &i, head, get_last_token(head));
		}
		else if (input[i] == '\'') // Single quotes
		{
			segment = extract_single_quote_content(input, &i);
			if (!segment)
				return (free_tokens(head)); // Return NULL after freeing tokens
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (input[i] == '"') // Double quotes
		{
			segment = extract_double_quote_content(input, &i, info);
			if (!segment)
				return (free_tokens(head)); // Return NULL after freeing tokens
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (input[i] == '$') // Variable
		{
			head = handle_env_variable(input, &i, head, &current_word_token, info);
		}
		else // Regular word character
		{
			segment = extract_word_segment(input, &i);
			if (segment) // Only process if we got something
				head = join_word_segment(segment, head, &current_word_token);
		}
		if (!head)
			return (NULL);  // If error occurred, return NULL
	}
	return (head);  // Return the list of tokens
}

int main(int ac, char **av, char **env)
{
	t_token	*token;
	t_info	info;
	char	*line;
	int		i;
	int		j;

	if (ac != 1 || av[1])
	{
		write(2, "Error: Invalid arguments\n", 24);
		return (1);
	}
	form_env(env, &info);
	using_history();
	while (1)
	{
		set_signals();
		info.pos = 0;
		info.flag_ri = 0;
		info.exec = NULL;
		info.tmp = NULL;
		//signal(SIGINT, ctrl_c);
		// signal(SIGQUIT, estat);
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!line)
		{
			write(1, "exit\n", 5);  // Print exit message on Ctrl+D
			break;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			token = tokenize_input(line, &info);  // Tokenize the input line with info
			if (!token)
			{
				free(line);
				continue;
			}
			if (!validate_syntax(token))
			{
				free_tokens(token);
				continue;
				//return (0); // or skip execution
			}
			if (token)
			{
				printf("%d\n", token->type);
				form_main(token, &info);
				i = 0;
				while (info.exec[i])
				{
					j = 0;
					//arg_execve(&info.exec[i], &info);
					while (info.exec[i][j])
					{
						printf("%s\n", info.exec[i][j]);
						j++;
					}
					printf("----------------------\n");
					i++;
					fflush(stdout);
				}
				free_tokens(token);  // Use your token free function
				ft_execution(&info);
			}
		}
		free(line);  // Free the line after processing
	}
	clear_history();
	free_mat(info.env);
	return (0);
}
