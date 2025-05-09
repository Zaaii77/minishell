/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:50:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/12 14:31:31 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Alloue la mémoire pour les pipes */
static int	allocate_pipes(t_data *data, int pipe_count)
{
	int	i;

	data->pipes = (int **)malloc(sizeof(int *) * pipe_count);
	if (!data->pipes)
		return (1);
	i = 0;
	while (i < pipe_count)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
		{
			free_pipes(data, i);
			free(data->pipes);
			data->pipes = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/* Crée les pipes et gère les erreurs potentielles */
int	create_pipes(t_data *data, int pipe_count)
{
	int	i;

	if (pipe_count <= 0)
		return (1);
	if (allocate_pipes(data, pipe_count) != 0)
		return (free_pipes(data, pipe_count), 1);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(data->pipes[i]) < 0)
		{
			close_all_pipes(data, i);
			free_pipes(data, pipe_count);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Alloue la mémoire pour les PIDs des processus enfants */
pid_t	*allocate_pids(int cmd_count, int pipe_count, t_data *data)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		free_pipes(data, pipe_count);
		return (NULL);
	}
	return (pids);
}

/* Libère la mémoire allouée pour les PIDs */
void	free_pids(pid_t *pids)
{
	if (pids)
		free(pids);
	pids = NULL;
}
