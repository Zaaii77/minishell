/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:04:28 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/11 20:23:11 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}

void	signal_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	setup_signals(t_data *data)
{
	signal(SIGINT, signal_handler_main);
	if (g_exit_status == 130 || g_exit_status == 131)
	{
		data->exit_status = g_exit_status;
		g_exit_status = 0;
	}
	signal(SIGQUIT, SIG_IGN);
}

void	setup_exec_signals(void)
{
	signal(SIGINT, ft_exec_sig_handler);
}
