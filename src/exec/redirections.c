/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:40:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/22 10:54:26 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Ouvre un fichier pour une redirection donnée */
static int	open_redirection_file(char *file, int flags)
{
	int		fd;
	char	*tmp;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell: ", file);
		if (!tmp)
			return (-1);
		perror(tmp);
		free(tmp);
		if (is_directory(file) || errno == EISDIR)
			g_exit_status = 126;
		else if (errno == EROFS || errno == ENOSPC
			|| errno == EEXIST || errno == EACCES
			|| errno == ENOTDIR)
			g_exit_status = 1;
		else
			g_exit_status = 0;
	}
	else
		close(fd);
	return (fd);
}

/* Crée les fichiers pour les redirections de sortie */
static int	create_redirection_files(t_redir *redirections)
{
	int	flags;

	while (redirections)
	{
		if (redirections->type == TOKEN_REDIR_OUT)
			flags = O_CREAT | O_WRONLY | O_TRUNC;
		else if (redirections->type == TOKEN_REDIR_APPEND)
			flags = O_CREAT | O_WRONLY | O_APPEND;
		else if (redirections->type == TOKEN_REDIR_IN)
			flags = O_RDONLY;
		else
		{
			redirections = redirections->next;
			continue ;
		}
		if (open_redirection_file(redirections->file, flags) == -1)
			return (-1);
		redirections = redirections->next;
	}
	return (0);
}

/* Gère la redirection heredoc */
static int	handle_heredoc_redirection(t_redir *redirection,
		t_data *data, t_cmd *cmd)
{
	int		fd_in;
	char	*heredoc_file;

	if (handle_heredoc(redirection->file, &heredoc_file, data, cmd) != 0)
		return (1);
	fd_in = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd_in == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd_in);
		return (1);
	}
	close(fd_in);
	return (-1);
}

/* Gère une redirection spécifique */
static int	handle_single_redirection(t_redir *redirection,
		t_data *data, t_cmd *cmd)
{
	if (redirection->type == TOKEN_REDIR_IN)
		return (handle_input_redirection(redirection->file));
	else if (redirection->type == TOKEN_REDIR_OUT)
		return (handle_output_redirection(redirection->file, 0));
	else if (redirection->type == TOKEN_REDIR_APPEND)
		return (handle_output_redirection(redirection->file, 1));
	else if (redirection->type == TOKEN_REDIR_HEREDOC)
		return (handle_heredoc_redirection(redirection, data, cmd));
	return (0);
}

/* Configure les redirections pour une commande */
int	setup_redirections(t_redir *redirections, t_data *data, t_cmd *cmd)
{
	if (create_redirection_files(redirections) != 0)
		return (1);
	while (redirections)
	{
		if (handle_single_redirection(redirections, data, cmd) == -1)
			return (1);
		redirections = redirections->next;
	}
	return (0);
}
