/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:50:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/12 18:41:38 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Supprime tous les fichiers commençant par .minishell_ */
void	delete_temp_files(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strncmp(entry->d_name, ".minishell_", 11) == 0)
			unlink(entry->d_name);
	}
	closedir(dir);
}

/* Libère tous les membres de la structure data */
void	free_data_members(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->env && data->env[0])
		free_tab(data->env);
	if (data->env_list)
		free_env_copy(data->env_list);
	if (data->path)
		free(data->path);
	if (data->cmd_list)
	{
		free_cmd_list(data->cmd_list);
		data->cmd_list = NULL;
	}
}

/* Nettoie et libère toutes les ressources avant de quitter le programme */
void	exit_clean(t_data *data, t_token *tokens, int i)
{
	if (!data && !tokens)
		exit(i);
	if (tokens)
	{
		free_token(tokens);
		tokens = NULL;
	}
	if (data)
		free_data_members(data);
	if (data->pipes)
	{
		if (data->cmd_list)
			free_pipes(data, count_commands(data->cmd_list) - 1);
		else
			free_pipes(data, 0);
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
	exit(i);
}

/* Vérifie si une chaîne est un argument numérique valide */
static int	is_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Gère la commande exit */
void	ft_exit(char **args, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!args[1])
		exit_clean(data, NULL, data->exit_status);
	if (!is_numeric_argument(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_clean(data, NULL, 2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_atoi(args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit_clean(data, NULL, exit_code);
}
