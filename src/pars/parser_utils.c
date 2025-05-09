/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:13:49 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/22 10:49:31 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirection_token(t_cmd *current_cmd, t_token **tokens,
	t_cmd *cmd_list)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (g_exit_status = 2, 0);
	}
	return (handle_redirection_file(current_cmd, tokens, cmd_list));
}

int	handle_heredoc_token(t_cmd *current_cmd, t_token **tokens,
	t_cmd *cmd_list, t_data *data)
{
	char	*heredoc_file;

	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (g_exit_status = 2, 0);
	}
	if (handle_heredoc((*tokens)->next->value,
			&heredoc_file, data, cmd_list) != 0)
	{
		free(heredoc_file);
		return (0);
	}
	add_redirection(&current_cmd->redirections, TOKEN_REDIR_IN, heredoc_file);
	if (!current_cmd->redirections)
	{
		free(heredoc_file);
		free_cmd_list(cmd_list);
		return (0);
	}
	*tokens = (*tokens)->next;
	return (1);
}

t_cmd	*initialize_command(t_cmd **current_cmd, t_cmd *cmd_list)
{
	*current_cmd = create_new_command();
	if (!*current_cmd)
	{
		free_cmd_list(cmd_list);
		return (NULL);
	}
	if (!cmd_list)
		cmd_list = *current_cmd;
	return (cmd_list);
}

int	process_token(t_cmd **current_cmd, t_cmd **cmd_list,
	t_token **tokens, t_data *data)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		if (!handle_word_token(*current_cmd, *tokens, *cmd_list))
			return (0);
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		if (!handle_pipe_token(current_cmd, *cmd_list))
			return (0);
	}
	else if ((*tokens)->type == TOKEN_REDIR_OUT
		|| (*tokens)->type == TOKEN_REDIR_APPEND
		|| (*tokens)->type == TOKEN_REDIR_IN)
	{
		if (!handle_redirection_token(*current_cmd, tokens, *cmd_list))
			return (0);
	}
	else if ((*tokens)->type == TOKEN_REDIR_HEREDOC)
	{
		if (!handle_heredoc_token(*current_cmd, tokens, *cmd_list, data))
			return (0);
	}
	return (1);
}

int	finalize_command(t_cmd *current_cmd, t_cmd *cmd_list)
{
	if (current_cmd && !current_cmd->args && !current_cmd->redirections)
	{
		free_cmd_list(cmd_list);
		free(current_cmd);
		return (0);
	}
	return (1);
}
