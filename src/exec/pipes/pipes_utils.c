/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:22 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/23 19:14:49 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Configure les pipes pour le processus enfant */
void	setup_child_pipes(t_data *data, int i, int cmd_count)
{
	if (i > 0)
	{
		if (dup2(data->pipes[i - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit_clean(data, NULL, 0);
		}
	}
	if (i < cmd_count - 1)
	{
		if (dup2(data->pipes[i][1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit_clean(data, NULL, 0);
		}
	}
	close_all_pipes(data, cmd_count - 1);
}

/* Gère les erreurs de fork et nettoie les ressources */
int	handle_fork_error(pid_t *pids, int i,
	t_data *data, int pipe_count)
{
	perror("fork");
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	free_pids(pids);
	close_all_pipes(data, pipe_count);
	free_pipes(data, pipe_count);
	return (1);
}

/* Gère les erreurs de commande non trouvée */
void	handle_command_not_found(t_cmd *current,
	t_data *data, int pipe_count)
{
	if (current && current->args && current->args[0])
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(current->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	close_all_pipes(data, pipe_count);
	free_pipes(data, pipe_count);
	exit_clean(data, NULL, 127);
}

/* Libère les ressources après l'exécution des processus */
void	cleanup_execution(t_data *data, pid_t *pids, int pipe_count)
{
	free_pids(pids);
	free_pipes(data, pipe_count);
}

/* Attend les processus enfants et gère les statuts */
int	wait_children(pid_t *pids, int cmd_count, int *exit_status)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			*exit_status = 130;
			break ;
		}
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != *exit_status)
				*exit_status = WEXITSTATUS(status);
		i++;
	}
	return (g_exit_status = *exit_status, *exit_status);
}
