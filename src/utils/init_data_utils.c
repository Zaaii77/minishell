/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:08:16 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/12 13:24:53 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**cpy_env;

	i = 0;
	while (env[i])
		i++;
	cpy_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cpy_env)
		return (NULL);
	cpy_env[i] = NULL;
	i = 0;
	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		if (!cpy_env[i])
			return (free_tab(cpy_env), NULL);
		i++;
	}
	return (cpy_env);
}

/* Récupère la variable d'environnement PATH */
char	*get_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i]);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

/* Crée un nœud de la liste chaînée pour une variable d'environnement */
int	create_env_node(t_env **env_list, char *env_var)
{
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		return (0);
	*equal_sign = '\0';
	name = ft_strdup(env_var);
	if (!name)
		return (1);
	*equal_sign = '=';
	if (!name)
		return (1);
	value = ft_strdup(equal_sign + 1);
	if (!value)
		return (free(name), 1);
	if (!add_value(env_list, name, value))
		return (free(name), free(value), 1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
