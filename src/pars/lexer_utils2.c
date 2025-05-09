/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:19:14 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 00:52:59 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_token(t_token **tokens, char *value, int type)
{
	t_token	*new;

	new = NULL;
	if (type == TOKEN_WORD && value)
	{
		value = process_value(value);
		if (!value)
			return ;
	}
	new = create_new_token(value, type);
	if (!new)
	{
		free(value);
		value = NULL;
		return ;
	}
	free(value);
	value = NULL;
	append_token(tokens, new);
}

char	*concatenate_parts(char *part1, char *part2)
{
	char	*result;

	if (!part1 && !part2)
		return (NULL);
	if (!part1)
	{
		result = ft_strdup(part2);
		if (!result)
			return (free(part2), part2 = NULL, NULL);
		return (free(part2), part2 = NULL, result);
	}
	if (!part2)
	{
		result = ft_strdup(part1);
		if (!result)
			return (free(part1), part1 = NULL, NULL);
		return (free(part1), part1 = NULL, result);
	}
	result = ft_strjoin(part1, part2);
	if (!result)
		return (free(part1), free(part2), NULL);
	return (free(part1), free(part2), part1 = NULL, part2 = NULL, result);
}

int	handle_escaped_characters(char *input, int *i,
	char **current_part, t_token **tokens)
{
	int		start;
	char	*escaped_part;

	start = ++(*i);
	(*i)++;
	escaped_part = ft_substr(input, start, 1);
	if (!escaped_part)
		return (free(*current_part), free_token(*tokens), -1);
	*current_part = concatenate_parts(*current_part, escaped_part);
	if (!*current_part)
		return (free_token(*tokens), -1);
	return (0);
}

int	handle_whitespace(char **current_part, t_token **tokens)
{
	if (*current_part)
	{
		add_token(tokens, *current_part, TOKEN_WORD);
		if (!*tokens)
			return (free_token(*tokens), -1);
		*current_part = NULL;
	}
	return (0);
}
