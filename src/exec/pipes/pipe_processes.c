/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:50:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/12 18:54:30 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Configure et exécute une commande dans un processus enfant */
static void	execute_child_command(t_cmd *current,
	t_data *data, int pipe_count, char *tmp)
{
	if (!tmp)
		handle_command_not_found(current, data, pipe_count);
	exec_cmd_in_child(current, data, tmp);
	close_all_pipes(data, pipe_count);
	free_pipes(data, pipe_count);
	exit_clean(data, NULL, 0);
}

/* Gère les commandes intégrées ou externes */
static void	handle_command_execution(t_cmd *current,
	t_data *data, int pipe_count, pid_t *pids)
{
	char	*tmp;
	int		result;

	result = 0;
	free_pids(pids);
	free_pipes(data, pipe_count);
	if (current && current->args && is_builtin(current->args[0]))
	{
		result = execute_builtin_with_redirections(current, data);
		close_all_pipes(data, pipe_count);
		free_pipes(data, pipe_count);
		exit_clean(data, NULL, result);
	}
	if (!current->args || !current->args[0])
		handle_command_not_found(current, data, pipe_count);
	tmp = find_command_path(current->args[0], data);
	if (!tmp)
		handle_command_not_found(current, data, pipe_count);
	execute_child_command(current, data, pipe_count, tmp);
}

/* Crée un processus enfant pour une commande */
static int	create_child_process(t_child *cp_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		setup_child_pipes(cp_data->data, cp_data->i, cp_data->cmd_count);
		handle_child_signals();
		if (setup_redirections(cp_data->current->redirections,
				cp_data->data, cp_data->current))
		{
			free_pids(cp_data->pids);
			close_all_pipes(cp_data->data, cp_data->pipe_count);
			free_pipes(cp_data->data, cp_data->pipe_count);
			exit_clean(cp_data->data, NULL, g_exit_status);
		}
		free_pipes(cp_data->data, cp_data->pipe_count);
		handle_command_execution(cp_data->current,
			cp_data->data, cp_data->pipe_count, cp_data->pids);
	}
	return (pid);
}

/* Crée les processus enfants pour chaque commande */
static int	create_child_processes(t_data *data,
	pid_t *pids, int cmd_count, int pipe_count)
{
	t_cmd	*current;
	t_child	cp_data;
	int		i;

	current = data->cmd_list;
	i = 0;
	while (current && i < cmd_count)
	{
		cp_data = (t_child){data, current, pids, i, cmd_count, pipe_count};
		pids[i] = create_child_process(&cp_data);
		if (pids[i] < 0)
			return (handle_fork_error(pids, i, data, pipe_count));
		current = current->next;
		i++;
	}
	return (0);
}

/* Exécute les processus avec pipes et attend leur terminaison */
int	exec_pipe(t_data *data, int cmd_count, int pipe_count)
{
	pid_t	*pids;
	int		exit_status;

	pids = allocate_pids(cmd_count, pipe_count, data);
	if (!pids)
		return (-1);
	if (create_child_processes(data, pids, cmd_count, pipe_count) != 0)
	{
		free_pids(pids);
		cleanup_on_interrupt(data, pipe_count);
		return (-1);
	}
	close_all_pipes(data, pipe_count);
	free_pipes(data, pipe_count);
	exit_status = 0;
	wait_children(pids, cmd_count, &exit_status);
	cleanup_execution(data, pids, pipe_count);
	return (exit_status);
}
