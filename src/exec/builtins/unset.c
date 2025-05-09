/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:30:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/22 10:53:53 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Supprime une variable de l'environnement */
static void	remove_env_var(t_env **env, char *name)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !name)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
		{
			free(current->name);
			free(current->value);
			if (prev)
				prev->next = current->next;
			else
				*env = (*env)->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/* Gère la suppression d'une variable d'environnement */
static int	process_unset_arg(char *arg, t_env **env, t_data *data)
{
	if (is_valid_identifier(arg))
	{
		remove_env_var(env, arg);
		if (!ft_strcmp(arg, "PATH"))
		{
			free(data->path);
			data->path = NULL;
		}
		return (0);
	}
	else
	{
		ft_printf("minishell: unset: `%s`: not a valid identifier\n", arg);
		return (1);
	}
}

/* Supprime des variables de l'environnement */
int	ft_unset(char **args, t_env **env, t_data *data)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[i])
		return (0);
	while (args[i])
	{
		status |= process_unset_arg(args[i], env, data);
		i++;
	}
	return (status);
}
