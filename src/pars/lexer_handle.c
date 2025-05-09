/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:20:06 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 00:34:19 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirections(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (handle_redirection_append(i, tokens));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (handle_redirection_heredoc(i, tokens));
	else if (input[*i] == '>')
		return (handle_redirection_out(i, tokens));
	else if (input[*i] == '<')
		return (handle_redirection_in(i, tokens));
	return (0);
}

int	handle_pipe(char *input, int *i, t_token **tokens)
{
	char	*pipe_token;

	pipe_token = NULL;
	if (input[*i] == '|')
	{
		pipe_token = ft_strdup("|");
		if (!pipe_token)
			return (free_token(*tokens), -1);
		add_token(tokens, pipe_token, TOKEN_PIPE);
		if (!*tokens)
			return (free_token(*tokens), -1);
		(*i)++;
	}
	return (0);
}

int	handle_special_characters(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (*current_part)
	{
		add_token(tokens, *current_part, TOKEN_WORD);
		if (!*tokens)
			return (free(*current_part), free_token(*tokens), -1);
		*current_part = NULL;
	}
	if (handle_redirections(input, i, tokens) == -1)
		return (-1);
	if (handle_pipe(input, i, tokens) == -1)
		return (-1);
	return (0);
}

int	handle_unquoted_part(char *input, int *i,
	char **current_part, t_token **tokens)
{
	int		start;
	char	*unquoted_part;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\'' && input[*i] != '\"'
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		(*i)++;
	unquoted_part = ft_substr(input, start, *i - start);
	if (!unquoted_part)
		return (free(*current_part), free_token(*tokens), -1);
	*current_part = concatenate_parts(*current_part, unquoted_part);
	if (!*current_part)
		return (free_token(*tokens), -1);
	return (0);
}

int	handle_escape_case(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (input[*i] == '\\' && input[*i + 1])
		return (handle_escaped_characters(input, i, current_part, tokens));
	return (0);
}
