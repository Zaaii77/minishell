/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:49:18 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/11 19:38:00 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Ferme tous les descripteurs de fichiers des pipes */
void	close_all_pipes(t_data *data, int pipe_count)
{
	int	i;

	if (!data->pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

/* Affiche un message d'erreur pour un identifiant invalide */
void	print_invalid_identifier_error(char *name)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/* Affiche le contenu d'un tableau de chaînes de caractères */
void	print_tab(char **tab)
{
	int	i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_printf("%s\n", tab[i]);
}

void	print_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->name, current->value);
		else
			ft_printf("%s\n", current->name);
		current = current->next;
	}
}
