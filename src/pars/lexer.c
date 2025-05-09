/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:28:49 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/23 14:43:42 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_input_char(char *input, int *i,
	char **current_part, t_token **tokens)
{
	if (handle_escape_case(input, i, current_part, tokens) == -1)
		return (-1);
	if (handle_whitespace_case(input, i, current_part, tokens) == -1)
		return (-1);
	if (handle_quote_case(input, i, current_part, tokens) == -1)
		return (-1);
	if (handle_special_char_case(input, i, current_part, tokens) == -1)
		return (-1);
	if (handle_default_case(input, i, current_part, tokens) == -1)
		return (-1);
	return (0);
}

int	finalize_tokens(char **current_part, t_token **tokens)
{
	if (*current_part)
	{
		add_token(tokens, *current_part, TOKEN_WORD);
		if (!*tokens)
		{
			if (*current_part)
				free(*current_part);
			*current_part = NULL;
			free_token(*tokens);
			return (-1);
		}
	}
	return (0);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	char	*current_part;

	tokens = NULL;
	i = 0;
	current_part = NULL;
	while (input && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input && input[i] == '\0')
		g_exit_status = 0;
	while (input && input[i])
	{
		if (process_input_char(input, &i, &current_part, &tokens) == -1)
			return (NULL);
	}
	if (finalize_tokens(&current_part, &tokens) == -1)
		return (NULL);
	return (tokens);
}
