/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:48:03 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/23 07:00:27 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
}

void	ft_clean_all(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}

void	signnn(void)
{
	signal(SIGINT, ft_clean_all);
	signal(SIGQUIT, ft_quit);
}
