/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:20:28 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/11 19:21:57 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_whitespace_case(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (input[*i] == ' ' || input[*i] == '\t')
	{
		if (handle_whitespace(current_part, tokens) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	handle_quotes(char *input, int i, char quote)
{
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n",
			STDERR_FILENO);
		return (g_exit_status = 2, -1);
	}
	return (i);
}

int	handle_quote_case(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (input[*i] == '\'' || input[*i] == '\"')
		return (handle_quotes_in_lexer(input, i, current_part, tokens));
	return (0);
}

int	handle_special_char_case(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (handle_special_characters(input, i, current_part, tokens));
	return (0);
}

int	handle_default_case(char *input, int *i,
	char **current_part, t_token **tokens)
{
	return (handle_unquoted_part(input, i, current_part, tokens));
}
