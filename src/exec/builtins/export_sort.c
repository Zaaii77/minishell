/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:30:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/11 19:40:45 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Échange les valeurs de deux nœuds de la liste */
static void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

/* Trie la liste des variables d'environnement */
void	sort_env_list(t_env **head)
{
	t_env	*a;
	t_env	*b;

	a = *head;
	while (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if (compare_env_vars(a, b) > 0)
				swap_env_nodes(a, b);
			b = b->next;
		}
		a = a->next;
	}
}

/* Affiche les variables d'environnement triées */
static void	print_sorted_vars(t_env *env_copy)
{
	while (env_copy)
	{
		ft_printf("declare -x %s=\"%s\"\n", env_copy->name, env_copy->value);
		env_copy = env_copy->next;
	}
}

/* Gère le cas où export est appelé sans valeur */
void	handle_export_no_value(t_env **env, char *name)
{
	t_env	*existing;

	existing = *env;
	while (existing)
	{
		if (ft_strncmp(existing->name, name, ft_strlen(name) + 1) == 0)
			return ;
		existing = existing->next;
	}
	add_value(env, name, "");
}

/* Affiche les variables d'environnement triées (pour export sans argument) */
int	print_sorted_env(t_env *env)
{
	t_env	*env_copy;
	t_env	*copy_head;

	env_copy = copy_env_list(env);
	if (!env_copy)
	{
		ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
		return (1);
	}
	sort_env_list(&env_copy);
	copy_head = env_copy;
	print_sorted_vars(env_copy);
	free_env_copy(copy_head);
	return (0);
}
