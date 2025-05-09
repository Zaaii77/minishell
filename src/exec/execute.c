/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:24:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/12 19:28:41 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Gère l'exécution dans le processus enfant */
static void	execute_child_process(t_cmd *cmd, t_data *data, char *pth)
{
	if (setup_redirections(cmd->redirections, data, cmd) != 0)
		exit_clean(data, NULL, 1);
	if (access(pth, F_OK) == -1)
	{
		ft_printf("minishell: %s:", cmd->args[0]);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (free(pth), exit_clean(data, NULL, 127));
	}
	if (access(pth, X_OK) == -1)
	{
		ft_printf("minishell: %s:", cmd->args[0]);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (free(pth), exit_clean(data, NULL, 126));
	}
	if (execve(pth, cmd->args, data->env) == -1)
	{
		ft_printf("minishell: %s:", cmd->args[0]);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (ft_putstr_fd("\n", 2), free(pth), exit_clean(data, 0, 126));
	}
}

/* Vérifie les redirections et retourne une erreur si nécessaire */
static int	handle_redir(t_cmd *cmd, t_data *data)
{
	if (setup_redirections(cmd->redirections, data, cmd) != 0)
		return (1);
	return (0);
}

/* Gère le processus enfant pour exécuter la commande */
static int	handle_child_process(t_cmd *cmd, t_data *data, char *cmd_path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, data, cmd_path);
	free(cmd_path);
	cmd_path = NULL;
	return (wait_for_child(pid));
}

/* Exécute une commande externe dans un processus enfant */
int	execute_external(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	int		validation_status;

	signal(SIGQUIT, ft_quit);
	if (!cmd || !cmd->args || !cmd->args[0])
		return (handle_redir(cmd, data));
	if (handle_redir(cmd, data) != 0)
		return (1);
	validation_status = validate_command(cmd, data, &cmd_path);
	if (validation_status != 0)
		return (validation_status);
	return (handle_child_process(cmd, data, cmd_path));
}

/* Exécute la liste des commandes avec ou sans pipes */
int	execute_commands(t_data *data)
{
	if (!data || !data->cmd_list)
		return (1);
	if (!data->cmd_list->next)
		return (execute_single_command(data->cmd_list, data));
	return (execute_piped_commands(data));
}
