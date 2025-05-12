/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:59:37 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/12 18:25:21 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built-ins/minishell.h"

int validate_syntax(t_token *tokens)
{
	t_token *prev = NULL;

	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (!prev || !tokens->next || tokens->next->type == TOKEN_PIPE)
			{
				printf("minishell: syntax error near unexpected token `%s'\n", token_type_to_string(TOKEN_PIPE));
				estat(2);
				return (0);
			}
		}
		else if (tokens->type == TOKEN_REDIR_IN || tokens->type == TOKEN_REDIR_OUT
			|| tokens->type == TOKEN_REDIR_APPEND || tokens->type == TOKEN_HEREDOC)
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `%s'\n", token_type_to_string(tokens->type));
				estat(2);
				return (0);
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1); // syntax OK
}

char *token_type_to_string(t_token_type token_type)
{
	if (token_type == TOKEN_WORD)
		return "word";
	else if (token_type == TOKEN_PIPE)
		return "|";
	else if (token_type == TOKEN_REDIR_IN)
		return "<";
	else if (token_type == TOKEN_REDIR_OUT)
		return ">";
	else if (token_type == TOKEN_REDIR_APPEND)
		return ">>";
	else if (token_type == TOKEN_SQUOTE)
		return "'";
	else if (token_type == TOKEN_DQUOTE)
		return "\"";
	else if (token_type == TOKEN_HEREDOC)
		return "<<";
	else if (token_type == TOKEN_VAR)
		return "$";
	else if (token_type == TOKEN_SPACE)
		return " ";
	else
		return "unknown";
}

