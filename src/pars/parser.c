/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:57 by lowatell          #+#             */
/*   Updated: 2025/04/04 18:02:00 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_redirection(t_redir **redirections, int type, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
	{
		*redirections = NULL;
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		return ;
	}
	new->type = type;
	new->file = file;
	new->next = NULL;
	if (!*redirections)
		*redirections = new;
	else
	{
		tmp = *redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	handle_word_token(t_cmd *cmd, t_token *token, t_cmd *cmd_list)
{
	char	*dup_value;
	char	**tmp;

	dup_value = ft_strdup(token->value);
	if (!dup_value)
	{
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		free_cmd_list(cmd_list);
		return (0);
	}
	tmp = ft_tabjoin(cmd->args, dup_value);
	if (!tmp)
	{
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		free_cmd_list(cmd_list);
		return (0);
	}
	cmd->args = tmp;
	return (1);
}

int	handle_pipe_token(t_cmd **current_cmd, t_cmd *cmd_list)
{
	if (!*current_cmd || (!(*current_cmd)->args
			&& !(*current_cmd)->redirections))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (g_exit_status = 2, 0);
	}
	(*current_cmd)->next = create_new_command();
	if (!(*current_cmd)->next)
	{
		free_cmd_list(cmd_list);
		return (0);
	}
	*current_cmd = (*current_cmd)->next;
	return (1);
}

int	handle_redirection_file(t_cmd *current_cmd, t_token **tokens,
	t_cmd *cmd_list)
{
	char	*file;

	file = ft_strdup((*tokens)->next->value);
	if (!file)
	{
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		return (0);
	}
	add_redirection(&current_cmd->redirections, (*tokens)->type, file);
	if (!current_cmd->redirections)
	{
		free(file);
		free_cmd_list(cmd_list);
		return (0);
	}
	*tokens = (*tokens)->next;
	return (1);
}

t_cmd	*parser(t_token *tokens, t_data *data)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
		{
			cmd_list = initialize_command(&current_cmd, cmd_list);
			if (!cmd_list)
				return (free_cmd_list(cmd_list), free(current_cmd), NULL);
		}
		if (!process_token(&current_cmd, &cmd_list, &tokens, data))
			return (free_cmd_list(cmd_list), NULL);
		tokens = tokens->next;
	}
	if (!finalize_command(current_cmd, cmd_list))
		return (free_cmd_list(cmd_list), free(current_cmd), NULL);
	return (cmd_list);
}
