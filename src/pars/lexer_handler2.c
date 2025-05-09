/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:19:37 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/23 13:10:24 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_quotes_in_lexer(char *input, int *i,
	char **current_part, t_token **tokens)
{
	int		start;
	char	*quoted_part;

	start = (*i)++;
	*i = handle_quotes(input, *i, input[start]);
	if (*i == -1)
		return (free(*current_part), free_token(*tokens), -1);
	quoted_part = ft_substr(input, start, *i - start + 1);
	if (!quoted_part)
		return (free(*current_part), free_token(*tokens), -1);
	*current_part = concatenate_parts(*current_part, quoted_part);
	if (!*current_part)
		return (free(quoted_part), free_token(*tokens), -1);
	(*i)++;
	return (0);
}

int	handle_redirection_append(int *i, t_token **tokens)
{
	char	*append_redir;

	append_redir = ft_strdup(">>");
	if (!append_redir)
		return (free_token(*tokens), -1);
	add_token(tokens, append_redir, TOKEN_REDIR_APPEND);
	if (!*tokens)
		return (free_token(*tokens), -1);
	*i += 2;
	return (0);
}

int	handle_redirection_heredoc(int *i, t_token **tokens)
{
	char	*heredoc_redir;

	heredoc_redir = ft_strdup("<<");
	if (!heredoc_redir)
		return (free_token(*tokens), -1);
	add_token(tokens, heredoc_redir, TOKEN_REDIR_HEREDOC);
	if (!*tokens)
		return (free_token(*tokens), -1);
	*i += 2;
	return (0);
}

int	handle_redirection_out(int *i, t_token **tokens)
{
	char	*out_redir;

	out_redir = ft_strdup(">");
	if (!out_redir)
		return (free_token(*tokens), -1);
	add_token(tokens, out_redir, TOKEN_REDIR_OUT);
	if (!*tokens)
		return (free_token(*tokens), -1);
	(*i)++;
	return (0);
}

int	handle_redirection_in(int *i, t_token **tokens)
{
	char	*in_redir;

	in_redir = ft_strdup("<");
	if (!in_redir)
		return (free_token(*tokens), -1);
	add_token(tokens, in_redir, TOKEN_REDIR_IN);
	if (!*tokens)
		return (free_token(*tokens), -1);
	(*i)++;
	return (0);
}
