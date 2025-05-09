/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:00:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/11 17:54:18 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Libère la liste des redirections d'une commande */
void	free_redirections(t_redir *redirections)
{
	t_redir	*current;
	t_redir	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

/* Libère un tableau de chaînes de caractères */
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

/* Libère la liste complète des commandes et leurs redirections */
void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		if (!tmp)
			break ;
		cmd_list = cmd_list->next;
		if (tmp && tmp->heredoc_file)
		{
			unlink(tmp->heredoc_file);
			free(tmp->heredoc_file);
		}
		if (tmp && tmp->args)
			free_tab(tmp->args);
		if (tmp && tmp->redirections)
			free_redirections(tmp->redirections);
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	cmd_list = NULL;
}

void	free_token(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	tokens = NULL;
}
