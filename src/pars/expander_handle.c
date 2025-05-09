/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:22:48 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 06:12:47 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_single_quotes(char *input, int *i, char *result)
{
	char	*tmp;

	tmp = ft_substr(input, (*i)++, 1);
	if (!tmp)
		return (free(result), NULL);
	result = append_char_to_result(result, tmp);
	if (!result)
		return (NULL);
	result = process_single_quotes_content(input, i, result);
	if (!result)
		return (NULL);
	tmp = ft_substr(input, (*i)++, 1);
	if (!tmp)
		return (free(result), NULL);
	return (append_char_to_result(result, tmp));
}

char	*handle_empty_dollar(char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (free(result), NULL);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_double_quotes(char *input, int *i,
	t_data *data, char *result)
{
	char	*tmp;

	tmp = ft_substr(input, (*i)++, 1);
	if (!tmp)
		return (NULL);
	result = append_char_to_result(result, tmp);
	if (!result)
		return (NULL);
	tmp = process_double_quotes_content(input, i, data, result);
	if (!tmp)
		return (free(result), NULL);
	if (!input[*i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed double quote\n",
			STDERR_FILENO);
		return (g_exit_status = 2, free(tmp), NULL);
	}
	result = ft_strdup(tmp);
	free(tmp);
	if (!result)
		return (NULL);
	tmp = ft_substr(input, (*i)++, 1);
	if (!tmp)
		return (NULL);
	return (append_char_to_result(result, tmp));
}

char	*handle_dollar_sign(char *input, int *i, t_data *data, char *result)
{
	if (!input[*i + 1])
	{
		result = handle_empty_dollar(result);
		if (!result)
			return (NULL);
		(*i)++;
		return (result);
	}
	return (expand_dollar_variable(input, i, data, result));
}

char	*handle_plain_text(char *input, int *i, char *result)
{
	char	*tmp;
	int		start;

	start = *i;
	while (input[*i] && input[*i] != '$'
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	tmp = ft_substr(input, start, *i - start);
	if (!tmp)
		return (free(result), NULL);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}
