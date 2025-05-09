/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:29:35 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 00:39:38 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Convertit le tableau d'environnement en liste chaînée */
t_env	*env_to_list(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		if (create_env_node(&env_list, env[i]))
		{
			free_env_copy(env_list);
			return (NULL);
		}
		i++;
	}
	return (env_list);
}

/* Helper function to join a path and command */
static char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

/* Helper function to search for the command in the paths */
static char	*search_command_in_paths(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path_and_cmd(paths[i], cmd);
		if (!cmd_path)
		{
			free_tab(paths);
			return (NULL);
		}
		if (access(cmd_path, X_OK) == 0)
			return (free_tab(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

/* Trouve le chemin complet d'une commande dans le PATH */
char	*find_command_path(char *cmd, t_data *data)
{
	char	**paths;
	t_env	*temp;
	char	*tmp;

	tmp = NULL;
	temp = data->env_list;
	if (!cmd || !data)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		tmp = ft_strdup(cmd);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = get_value(*temp, "PATH");
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	return (search_command_in_paths(paths, cmd));
}

/* Initialise la structure data avec les paramètres du programme */
t_data	*init_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	load_history();
	(void)ac;
	(void)av;
	data->input = NULL;
	data->env = copy_env(env);
	if (!data->env)
		return (free(data), NULL);
	data->env_list = env_to_list(data->env);
	if (!data->env_list)
		return (free_tab(data->env), NULL);
	data->path = get_path(data->env);
	if (!data->path)
		return (free_tab(data->env),
			free_env_copy(data->env_list), free(data), NULL);
	data->cmd_list = NULL;
	data->exit_status = 0;
	data->pipes = NULL;
	data->tokens = NULL;
	return (data);
}
