/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:25:20 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/23 15:18:35 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_exit_expansion(int *i, t_data *data, char *result)
{
	char	*tmp;

	tmp = ft_itoa(data->exit_status);
	if (!tmp)
		return (free(result), NULL);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	*i += 2;
	return (result);
}

static char	*handle_variable_expansion(char *input,
		int *i, t_data *data, char *result)
{
	char	*tmp;
	int		len;

	tmp = expand_variable(&input[*i], data->env_list, &len);
	if (!tmp)
		return (free(result), NULL);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	*i += len;
	return (result);
}

char	*handle_dollar_literal(int *i, char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (free(result), NULL);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

char	*expand_dollar_variable(char *input, int *i, t_data *data, char *result)
{
	if (input[*i + 1] == '?')
		result = handle_exit_expansion(i, data, result);
	else if (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_')
		result = handle_variable_expansion(input, i, data, result);
	else
		result = handle_dollar_literal(i, result);
	return (result);
}

char	*expand_variable(char *input, t_env *env_list, int *len)
{
	char	*name;
	char	*value;
	char	*result;
	int		i;

	i = 1;
	if (input[i] && ft_isdigit(input[i]))
		i++;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_')
		&& !ft_isdigit(input[1]))
		i++;
	*len = i;
	name = ft_substr(input, 1, i - 1);
	if (!name)
		return (NULL);
	if (!*name)
		return (free(name), ft_strdup("$"));
	value = get_value(*env_list, name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	result = ft_strdup(value);
	if (!result)
		return (NULL);
	return (result);
}
