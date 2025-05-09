/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:46:42 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/11 20:02:03 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exec_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_status = 130;
	}
}

void	load_history(void)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("./.shell_history", O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	if (!line)
		close(fd);
	while (line)
	{
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!tmp)
		{
			free(line);
			break ;
		}
		free(line);
		add_history(tmp);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
}

void	save_history(char *input)
{
	int		fd;
	char	*tmp;

	if (!input)
		return ;
	fd = open("./.shell_history", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return ;
	tmp = ft_strjoin(input, "\n");
	if (tmp)
	{
		ft_putstr_fd(tmp, fd);
		free(tmp);
		tmp = NULL;
	}
	close(fd);
}

char	*read_input(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		write(1, "exit\n", 5);
		exit_clean(data, 0, 0);
	}
	if (*input)
	{
		add_history(input);
		save_history(input);
	}
	return (input);
}
