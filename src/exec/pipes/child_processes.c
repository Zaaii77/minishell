/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:17:39 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 19:20:48 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	handle_no_cmd(t_cmd *cmd, t_data *data)
{
	ft_printf("minishell: %s: command not found\n", cmd->args[0]);
	exit_clean(data, NULL, 127);
}

static void	handle_execve_error(char *cmd_path, char *cmdpath, t_data *data)
{
	free(cmd_path);
	free(cmdpath);
	ft_printf("%s\n", strerror(errno));
	exit_clean(data, NULL, 126);
}

/* Exécute une commande dans un processus enfant */
int	exec_cmd_in_child(t_cmd *cmd, t_data *data, char *cmdpath)
{
	char	*cmd_path;

	if (setup_redirections(cmd->redirections, data, cmd) != 0)
		exit_clean(data, NULL, g_exit_status);
	if (is_builtin(cmd->args[0]))
		exit_clean(data, NULL, (execute_builtin(cmd, data)));
	cmd_path = find_command_path(cmd->args[0], data);
	if (!cmd_path)
		handle_no_cmd(cmd, data);
	if (access(cmd_path, F_OK) == -1)
	{
		free(cmd_path);
		ft_printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		exit_clean(data, NULL, 127);
	}
	signal(SIGQUIT, ft_quit);
	if (execve(cmd_path, cmd->args, data->env) < 0)
		handle_execve_error(cmd_path, cmdpath, data);
	return (0);
}
