/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:35:33 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/22 10:48:59 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*append_char_to_result(char *result, char *tmp)
{
	char	*new_result;

	new_result = ft_strjoin_free(result, tmp);
	free(tmp);
	if (!new_result)
		return (free(result), NULL);
	return (new_result);
}

char	*handle_exit_status_expansion(int *i,
	t_data *data, char *result)
{
	char	*tmp;

	tmp = ft_itoa(data->exit_status);
	if (!tmp)
		return (free(result), NULL);
	*i += 2;
	result = append_char_to_result(result, tmp);
	return (result);
}

char	*handle_dollar(int *i, char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (free(result), NULL);
	(*i)++;
	result = append_char_to_result(result, tmp);
	return (result);
}

char	*handle_single_char(char *input, int *i, char *result)
{
	char	*tmp;

	tmp = ft_substr(input, (*i)++, 1);
	if (!tmp)
		return (free(result), NULL);
	result = append_char_to_result(result, tmp);
	return (result);
}

int	check_after_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	i--;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'
			|| input[i] == '\n'))
		i--;
	if (i < 0 || input[i] != '|')
		return (1);
	return (0);
}
