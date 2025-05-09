/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:30:34 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/22 10:51:01 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*handle_variable_expansion(char *input, int *i,
		t_data *data, char *result)
{
	char	*tmp;
	int		len;

	tmp = expand_variable(&input[*i], data->env_list, &len);
	if (!tmp)
		return (free(result), NULL);
	*i += len;
	result = append_char_to_result(result, tmp);
	return (result);
}

char	*process_dollar_in_quotes(char *input, int *i,
	t_data *data, char *result)
{
	if (input[*i] == '$' && (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_'))
		result = handle_variable_expansion(input, i, data, result);
	else if (input[*i] == '$' && input[*i + 1] == '?')
		result = handle_exit_status_expansion(i, data, result);
	else if (input[*i] == '$' && (!input[*i + 1] || input[*i + 1] == ' '
			|| input[*i + 1] == '\t' || input[*i + 1] == '\n'
			|| input[*i + 1] == '"'))
		result = handle_dollar(i, result);
	else
		result = handle_single_char(input, i, result);
	if (!result)
		return (NULL);
	return (result);
}

char	*process_double_quotes_content(char *input, int *i,
	t_data *data, char *result)
{
	char	*tmp;
	char	*tmpp;

	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
			result = process_dollar_in_quotes(input, i, data, result);
		else
		{
			tmp = ft_substr(input, (*i)++, 1);
			if (!tmp)
				return (free(result), NULL);
			tmpp = ft_strjoin(result, tmp);
			free(tmp);
			if (!tmpp)
				return (free(result), NULL);
			free(result);
			result = ft_strdup(tmpp);
			free(tmpp);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

char	*process_single_quotes_content(char *input, int *i, char *result)
{
	char	*tmp;
	int		start;

	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed single quote\n",
			STDERR_FILENO);
		return (g_exit_status = 2, free(result), NULL);
	}
	tmp = ft_substr(input, start, *i - start);
	if (!tmp)
		return (free(result), NULL);
	result = append_char_to_result(result, tmp);
	if (!result)
		return (NULL);
	return (result);
}

char	*expander(char *input, t_data *data)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	if (!check_after_pipe(input))
		return (ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n",
				STDERR_FILENO), g_exit_status = 2, NULL);
	while (i >= 0 && input[i])
	{
		if (input[i] == '"')
			result = handle_double_quotes(input, &i, data, result);
		else if (input[i] == '\'')
			result = handle_single_quotes(input, &i, result);
		else if (input[i] == '$')
			result = handle_dollar_sign(input, &i, data, result);
		else
			result = handle_plain_text(input, &i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}
