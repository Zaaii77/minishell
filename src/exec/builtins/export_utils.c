/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:30:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/22 10:52:28 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Vérifie si un nom de variable est valide */
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Compare deux noms de variables pour le tri */
int	compare_env_vars(t_env *a, t_env *b)
{
	return (ft_strncmp(a->name, b->name, ft_strlen(a->name) + 1));
}

/* Copie la liste d'environnement pour le tri */
t_env	*copy_env_list(t_env *env)
{
	t_env	*env_copy;
	char	*name_copy;
	char	*value_copy;
	t_env	*current;

	env_copy = NULL;
	current = env;
	while (current)
	{
		name_copy = ft_strdup(current->name);
		value_copy = ft_strdup(current->value);
		if (!name_copy || !value_copy
			|| !add_value(&env_copy, name_copy, value_copy))
		{
			free(name_copy);
			free(value_copy);
			free_env_copy(env_copy);
			return (NULL);
		}
		current = current->next;
	}
	return (env_copy);
}

/* Libère la copie de la liste des variables d'environnement */
void	free_env_copy(t_env *env_copy)
{
	t_env	*temp;

	while (env_copy)
	{
		temp = env_copy;
		env_copy = env_copy->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
