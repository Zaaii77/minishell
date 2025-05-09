/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:50:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/12 14:34:03 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Compte le nombre total de commandes dans la liste */
int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	if (!cmd_list)
		return (0);
	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* Libère la mémoire allouée pour les pipes */
void	free_pipes(t_data *data, int pipe_count)
{
	int	i;

	if (!data || !data->pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
}

/* Vérifie le nombre de commandes et exécute la commande unique si nécessaire */
static int	check_cmd_count(t_data *data, int cmd_count)
{
	if (cmd_count <= 0)
		return (1);
	if (cmd_count == 1)
		return (execute_single_command(data->cmd_list, data));
	return (0);
}

/* Libère les ressources en cas d'interruption */
void	cleanup_on_interrupt(t_data *data, int pipe_count)
{
	close_all_pipes(data, pipe_count);
	free_pipes(data, pipe_count);
}

/* Exécute les commandes avec pipes entre elles */
int	execute_piped_commands(t_data *data)
{
	int		cmd_count;
	int		pipe_count;
	int		result;

	cmd_count = count_commands(data->cmd_list);
	result = check_cmd_count(data, cmd_count);
	if (result > 0)
		return (result);
	pipe_count = cmd_count - 1;
	if (create_pipes(data, pipe_count) != 0)
	{
		free_pipes(data, pipe_count);
		return (1);
	}
	result = exec_pipe(data, cmd_count, pipe_count);
	if (result == -1)
	{
		cleanup_on_interrupt(data, pipe_count);
		if (WIFEXITED(result))
			return (WEXITSTATUS(result));
		return (result);
	}
	return (setup_signals(data), result);
}
